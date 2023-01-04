#include "MainScene.h"

cocos2d::Scene* MainScene::createScene()
{
	MainScene* _sceneWithPhysics = create();
	_sceneWithPhysics->initWithPhysics();
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

	this->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
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

	if (m_pSelectedLemming != nullptr)
	{
		const cocos2d::Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
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
