#include "MainScene.h"

Scene* MainScene::createScene()
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
	m_visibleSize = designResolutionSize;
	m_visibleOrigin = { 0, 0 };

	m_pMap = new TileMap(tileMap_path);
	addChild(m_pMap->getMap());

	m_pSelectedLemming = nullptr;
	m_pLemmingPointer = nullptr;

	EventListenerMouse* _mouseEventListener = EventListenerMouse::create();
	_mouseEventListener->onMouseDown = CC_CALLBACK_1(MainScene::OnMouseClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseEventListener, this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	EventListenerPhysicsContact* _endListener = EventListenerPhysicsContact::create();
	_endListener->onContactBegin = CC_CALLBACK_1(MainScene::OnLemmingContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_endListener, this);
	scheduleUpdate();

	return true;
}

void MainScene::onEnter()
{
	Scene::onEnter();

	Sprite* _sp = Sprite::create(tileMap_netherPortal_asset_path);
	assert(_sp);
	_sp->setPosition(m_pMap->getSpawnPoint());
	addChild(_sp);

	AddWindowsEdgesCollider();
	CreateDynamicMenu();

	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

void MainScene::update(float delta)
{
	Node::update(delta);

	if (!m_loaded)
	{
		const time_t time = std::time(nullptr);

		if (time < m_nextSpawn) goto next;

		AddLemming(m_pMap->getSpawnPoint().x, m_pMap->getSpawnPoint().y);
		m_lemmingsSpawned += 1;
		m_nextSpawn = time + 2;

		switch (m_lemmingsSpawned)
		{
		case 1:
			m_pSelectedLemming = m_lemmings[0];
			CreateLemmingSelector();
			break;
		default:
			break;
		}

		if (m_lemmingsSpawned == m_totalLemmings) m_loaded = true;
	}
next:
	if (m_pSelectedLemming != nullptr)
	{
		const Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
		m_pLemmingPointer->setPosition({
			_targetLemmingPos.x, _targetLemmingPos.y
			});
		m_pLemmingPointer->setRotation(m_pLemmingPointer->getRotation() + 1);
		m_pLemmingPointer->setVisible(true);
		return;
	}
	m_pLemmingPointer->setVisible(false);

	if (m_lemmingsEnded == m_totalLemmings)
	{
		Scene* _winScene = WinMenu::create();
		std::map<std::string, int>* stats = new std::map<std::string, int>;
		(*stats)["total"] = m_totalLemmings;
		(*stats)["ended"] = m_lemmingsEnded;
		_winScene->setUserData((void*)stats);
		Director::getInstance()->pushScene(_winScene);
	}
}

void MainScene::CreateDynamicMenu()
{
	DrawNode* _draw = DrawNode::create();
	_draw->drawSolidRect(
		Vec2(0, 0),
		Vec2(m_visibleSize.width, m_visibleSize.height / 7),
		Color4F(255, 255, 255, 50)
	);
	addChild(_draw);

	MenuItemImage* _action1 = MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_0(MainScene::CapacityAction, this, MINING)
	);
	assert(_action1);
	_action1->setAnchorPoint(Vec2(0, 0));
	_action1->setPosition(Vec2(
		m_visibleOrigin.x,
		m_visibleOrigin.y)
	);
	_action1->setScale(4);

	Menu* _menu = Menu::create(_action1, NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}

bool MainScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Scene* _pauseScene = PauseMenu::create();
		Director::getInstance()->pushScene(_pauseScene);
		return true;
	}
	return false;
}

void MainScene::AddWindowsEdgesCollider()
{
	PhysicsBody* _body = PhysicsBody::createEdgeBox(
		{ m_visibleSize.width, m_visibleSize.height + 2 },
		PhysicsMaterial(PHYSICSBODY_MATERIAL_DEFAULT),
		1
	);
	_body->setCategoryBitmask(window_collision_mask_id);
	_body->setCollisionBitmask(lemming_collision_mask_id);
	_body->setContactTestBitmask(test_collision_mask_id);

	Node* _edgeShape = Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height / 2
	);
	addChild(_edgeShape);
}

void MainScene::AddLemming(float positionX, float positionY)
{
	Lemming* _l = Lemming::create(lemming_asset_filePath, { positionX, positionY });
	addChild(_l);
	m_lemmings.push_back(_l);
}

bool MainScene::OnLemmingContactBegin(const PhysicsContact& contact)
{
	PhysicsBody* _shapeA = contact.getShapeA()->getBody();
	PhysicsBody* _shapeB = contact.getShapeB()->getBody();

	if ((_shapeA->getCategoryBitmask() == lemming_collision_mask_id && _shapeB->getContactTestBitmask() == lemming_collision_mask_id) ||
		(_shapeA->getContactTestBitmask() == lemming_collision_mask_id && _shapeB->getCategoryBitmask() == lemming_collision_mask_id)) {
		m_lemmingsEnded += 1;

		Node* _node = nullptr;
		unsigned int _index = 0;

		if (_shapeA->getCategoryBitmask() == lemming_collision_mask_id) _node = _shapeA->getNode();
		else _node = _shapeB->getNode();

		for (_index; _index < m_lemmings.size(); _index++)
		{
			if (m_lemmings[_index] != _node) continue;
			if (m_pSelectedLemming == m_lemmings[_index]) m_pSelectedLemming = nullptr;
			m_lemmings[_index]->removeFromParent();
			m_lemmings[_index]->release();
			break;
		}

		m_lemmings.erase(m_lemmings.begin() + _index);

		return true;
	}

	return false;
}

void MainScene::CreateLemmingSelector()
{
	Sprite* _sp = Sprite::create(lemming_selector_asset_path);
	assert(_sp);
	_sp->setPosition(m_pSelectedLemming->getPosition());
	m_pLemmingPointer = _sp;
	m_pLemmingPointer->setVisible(false);
	addChild(m_pLemmingPointer);
}

bool MainScene::OnMouseClick(Event* event)
{
	const auto* _mouseEvent = dynamic_cast<EventMouse*>(event);

	const Vec2 _cursorPos = { _mouseEvent->getCursorX(), _mouseEvent->getCursorY() };

	switch (_mouseEvent->getMouseButton())
	{
	case EventMouse::MouseButton::BUTTON_LEFT:
		return MouseLeftClickCallBack(_cursorPos);
	case EventMouse::MouseButton::BUTTON_RIGHT:
		return m_pMap->removeTileUnder(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2);
	case EventMouse::MouseButton::BUTTON_4:
		return m_pMap->removeTileRight(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2);
	case EventMouse::MouseButton::BUTTON_5:
		return m_pMap->removeTileLeft(m_pSelectedLemming->getPosition() + m_pSelectedLemming->getSpriteSize() / 2);
	default:
		return false;
	}
}

bool MainScene::MouseLeftClickCallBack(Vec2 mouseCoordinates)
{
	for (Lemming*& _l : m_lemmings)
	{
		if (_l->getPhysicsBody()->getShape(0)->containsPoint(mouseCoordinates))
		{
			m_pLemmingPointer->setVisible(true);
			m_pSelectedLemming = _l;
			return true;
		}
	}
	m_pSelectedLemming = nullptr;
	return false;
}

void MainScene::CapacityAction(Actions actionState)
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