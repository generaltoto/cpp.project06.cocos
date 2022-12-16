#include "MainScene.h"

cocos2d::Scene* MainScene::createScene()
{
	MainScene* _sceneWithPhysics = create();
	_sceneWithPhysics->initWithPhysics();
	_sceneWithPhysics->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	return _sceneWithPhysics;
}

bool MainScene::init()
{
	if (!initWithPhysics()) return false;

	m_visibleSize = designResolutionSize;
	m_visibleOrigin = { 0, 0 };

	m_pMap = new TileMap(tileMap_path);

	m_pSelectedLemming = nullptr;
	m_pLemmingPointer = nullptr;

	addChild(m_pMap->getMap());


	cocos2d::EventListenerMouse* _mouseEventListener = cocos2d::EventListenerMouse::create();
	_mouseEventListener->onMouseDown = CC_CALLBACK_1(MainScene::OnMouseClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseEventListener, this);

	cocos2d::EventListenerPhysicsContact* _contactListener = cocos2d::EventListenerPhysicsContact::create();
	_contactListener->onContactPreSolve = CC_CALLBACK_1(MainScene::onContactPreSolve, this);
	_contactListener->onContactPostSolve = CC_CALLBACK_1(MainScene::onContactPostSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	scheduleUpdate();

	//region Keyboard Listener
	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	cocos2d::Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	keyboardListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		keys.push_back(keyCode);
		cocos2d::Scene* _pauseScene = PauseMenu::create();
		cocos2d::Director::getInstance()->pushScene(_pauseScene);
	};
	keyboardListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		// remove the key.
		keys.erase(std::remove(keys.begin(), keys.end(), keyCode), keys.end());
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	//endregion

	return true;
}

void MainScene::onEnter()
{
	cocos2d::Scene::onEnter();

	const cocos2d::Vec2 _middleScreen = { m_visibleSize.width / 2, m_visibleSize.height / 2 };

	cocos2d::Sprite* _sp = cocos2d::Sprite::create(tileMap_netherPortal_asset_path);
	assert(_sp);
	_sp->setPosition(m_pMap->getSpawnPoint());
	addChild(_sp);

	for (int i = 0; i < 3; i++) addLemming(_middleScreen.x + (300.f * i), _middleScreen.y);
	m_pSelectedLemming = m_lemmings[0];
	CreateLemmingSelector();

	addWindowsEdgesCollider();
}

bool MainScene::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
	// Check if the key is pressed
	if (std::find(keys.begin(), keys.end(), code) != keys.end())
		return true;
	return false;
}

void MainScene::update(float delta)
{
	Node::update(delta);

	for (const auto& lem : m_lemmings) lem->checkIfFalling();

	if (m_pSelectedLemming != nullptr)
	{
		const cocos2d::Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
		const cocos2d::Vec2 _targetLemmingSize = m_pSelectedLemming->getSpriteSize();
		m_pLemmingPointer->setPosition({
			_targetLemmingPos.x, _targetLemmingPos.y
			});
		m_pLemmingPointer->setRotation(m_pLemmingPointer->getRotation() + 1);
		m_pLemmingPointer->setVisible(true);
		return;
	}
	m_pLemmingPointer->setVisible(false);
}

bool MainScene::OnMouseClick(cocos2d::Event* event)
{
	const auto* _mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);

	const cocos2d::Vec2 _cursorPos = { _mouseEvent->getCursorX(), _mouseEvent->getCursorY() };

	if (_mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
		m_pSelectedLemming = MouseLeftClickCallBack(_cursorPos);

	return false;
}

bool MainScene::onContactPreSolve(cocos2d::PhysicsContact& contact) const
{
	cocos2d::PhysicsBody* _shapeA = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* _shapeB = contact.getShapeB()->getBody();

	// Saving velocity to restore it at the end of collide (prevent from friction slow down)
	const auto _velocityData = new float[2];
	_velocityData[0] = _shapeA->getVelocity().length();
	_velocityData[1] = _shapeB->getVelocity().length();
	contact.setData(_velocityData);
	// See MainScene::onContactPostSolve for use of saved data

	// Checking if a Lemming collided with a window border
	if (_shapeA->getCollisionBitmask() == lemming_collision_mask_id && _shapeB->getCollisionBitmask() == window_collision_mask_id
		|| _shapeA->getCollisionBitmask() == window_collision_mask_id && _shapeB->getCollisionBitmask() == lemming_collision_mask_id
		)
	{
		Lemming* _l = getLemmingWithName(_shapeB->getName());
		if (_l == nullptr) return false;
		lemmingContactWithWindowBordersCallback(_l);
		return true;
	}
	return false;
}

bool MainScene::onContactPostSolve(const cocos2d::PhysicsContact& contact) const
{
	cocos2d::PhysicsBody* _shapeA = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* _shapeB = contact.getShapeB()->getBody();

	/*
	 * Restoring the velocity, keeping the direction of the velocity.
	 * Does not restore the y velocity. You you want to, replace '{ va.x * v[0], 0 }' by 'va.x * v[0]'.
	 */
	cocos2d::Vec2 _va = _shapeA->getVelocity();
	cocos2d::Vec2 _vb = _shapeB->getVelocity();
	_va.normalize();
	_vb.normalize();

	const auto _v = static_cast<float*>(contact.getData());
	_shapeA->setVelocity({ _va.x * _v[0], 0 });
	_shapeB->setVelocity({ _vb.x * _v[1], 0 });
	delete _v;

	return true;
}

void MainScene::addWindowsEdgesCollider()
{
	cocos2d::PhysicsBody* _body = cocos2d::PhysicsBody::createEdgeBox(
		{ m_visibleSize.width, m_visibleSize.height + 2 },
		cocos2d::PhysicsMaterial(cocos2d::PHYSICSBODY_MATERIAL_DEFAULT),
		1
	);
	_body->setCategoryBitmask(window_collision_mask_id);
	_body->setCollisionBitmask(lemming_collision_mask_id);
	_body->setContactTestBitmask(test_collision_mask_id);
	_body->setName(window_collision_name_template);

	cocos2d::Node* _edgeShape = cocos2d::Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height / 2
	);
	addChild(_edgeShape);
}

void MainScene::addLemming(float positionX, float positionY)
{
	Lemming* _l = Lemming::create(lemming_asset_filePath, { positionX, positionY });
	addChild(_l);
	m_lemmings.push_back(_l);
	m_indexedLemmings.insert(std::make_pair(_l->getName(), _l));
}

void MainScene::CreateLemmingSelector()
{
	cocos2d::Sprite* _sp = cocos2d::Sprite::create(lemming_selector_asset_path);
	assert(_sp);
	const cocos2d::Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
	const cocos2d::Vec2 _targetLemmingSize = m_pSelectedLemming->getSpriteSize();
	_sp->setPosition({
		_targetLemmingPos.x, _targetLemmingPos.y
		});
	m_pLemmingPointer = _sp;
	m_pLemmingPointer->setVisible(false);
	addChild(m_pLemmingPointer);
}

void MainScene::lemmingContactWithWindowBordersCallback(Lemming* lemming)
{
	cocos2d::PhysicsBody* _body = lemming->getPhysicsBody();
	cocos2d::Vec2 _curVelocity = _body->getVelocity();

	if (isFloatNull(_curVelocity.x) && isFloatNull(_curVelocity.y) && lemming->m_currentState == WALKING)
	{
		lemming->m_currentAcceleration *= -1;
		_body->setVelocity({ _curVelocity.x * lemming->m_currentAcceleration, _curVelocity.y });
	}
	if (isFloatNull(_curVelocity.y) && lemming->m_currentState == FALLING)
	{
		_body->setVelocity({ lemming->m_lemmingVelocity,0 });
		lemming->m_currentState = WALKING;
	}
}

Lemming* MainScene::MouseLeftClickCallBack(cocos2d::Vec2 mouseCoordinates)
{
	for (Lemming*& _l : m_lemmings)
	{
		if (isInRectCoordinates(_l->getPosition(), _l->getSpriteSize(), mouseCoordinates))
		{
			m_pLemmingPointer->setVisible(true);
			return _l;
		}
	}
	return nullptr;
}

Lemming* MainScene::getLemmingWithName(const std::string& name) const
{
	const auto it = m_indexedLemmings.find(name);
	if (it == m_indexedLemmings.end()) return nullptr;
	return it->second;
}
