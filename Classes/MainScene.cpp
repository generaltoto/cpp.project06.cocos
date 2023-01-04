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

	m_loaded = false;
	m_nextSpawn = std::time(nullptr);

	// DEBUG
	m_mouseText = cocos2d::Label::createWithTTF("TEST", "fonts/arial.ttf", 24);
	m_mouseText->setPosition(cocos2d::Vec2(100, 100));
	m_mouseText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	addChild(m_mouseText, 999);
	// DEBUG

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
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
			cocos2d::Scene* _pauseScene = PauseMenu::create();
			cocos2d::Director::getInstance()->pushScene(_pauseScene);
		}
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


	addWindowsEdgesCollider();
	createDynamicMenu();

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

	if (!m_loaded)
	{
		time_t time = std::time(nullptr);

		if (time < m_nextSpawn) goto next;

		addLemming(m_pMap->getSpawnPoint().x, m_pMap->getSpawnPoint().y);
		m_nextSpawn = time + 5;

		switch (m_lemmings.size())
		{
		case 1:
			m_pSelectedLemming = m_lemmings[0];
			CreateLemmingSelector();
			break;
		case 3:
			m_loaded = true;
			break;
		default:
			break;
		}
	}
	next:
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

void MainScene::createDynamicMenu()
{
	cocos2d::DrawNode* _draw = cocos2d::DrawNode::create();
	_draw->drawSolidRect(
		cocos2d::Vec2(
			0,
			0
		),
		cocos2d::Vec2(
			m_visibleSize.width,
			m_visibleSize.height / 7
		),
		cocos2d::Color4F(255, 255, 255, 50)
	);
	addChild(_draw);

	cocos2d::MenuItemImage* _action1 = cocos2d::MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_0(MainScene::capaAction, this, MINING)
	);
	assert(_action1);
	_action1->setAnchorPoint(cocos2d::Vec2(0, 0));
	_action1->setPosition(cocos2d::Vec2(
		m_visibleOrigin.x,
		m_visibleOrigin.y)
	);
	_action1->setScale(4);

	cocos2d::Menu* _menu = cocos2d::Menu::create(_action1, NULL);
	_menu->setPosition(cocos2d::Vec2::ZERO);
	addChild(_menu, 1);
}

bool MainScene::OnMouseClick(cocos2d::Event* event)
{
	const auto* _mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);

	const cocos2d::Vec2 _cursorPos = { _mouseEvent->getCursorX(), _mouseEvent->getCursorY() };

	if (_mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//m_pSelectedLemming = MouseLeftClickCallBack(_cursorPos);

		if (m_pMap->getTileUnder(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2) == nullptr) return false;
		m_mouseText->setPosition(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2);
		m_mouseText->setString(std::to_string(round(m_pSelectedLemming->getPosition().y / 64)));
		
		m_pMap->removeTileUnder(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2);
	}

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

void MainScene::capaAction(Actions actionState)
{
	switch (actionState)
	{
	case MINING:
		CCLOG("Je mine");
		break;
	case BUILDING:
		CCLOG("Je construis");
		break;
	case RESET:
		break;
	default:
		break;
	}
}