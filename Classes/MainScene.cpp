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
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

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
		const Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
		m_pLemmingPointer->setPosition({
			_targetLemmingPos.x, _targetLemmingPos.y
			});
		m_pLemmingPointer->setRotation(m_pLemmingPointer->getRotation() + 1);
		m_pLemmingPointer->setVisible(true);
		return;
	}
	m_pLemmingPointer->setVisible(false);
}

void MainScene::CreateDynamicMenu()
{
	DrawNode* _draw = DrawNode::create();
	_draw->drawSolidRect(
		Vec2(0, m_visibleSize.height),
		Vec2(m_visibleSize.width, m_visibleSize.height / 8 * 7),
		Color4F(255, 255, 255, 50)
	);
	addChild(_draw,2);

	Label* _label = Label::createWithTTF("Lemmings : " + m_lemmings.size(), font_path, 40);
	assert(_label);
	_label->setAnchorPoint(Vec2(0.5, 0.5));
	_label->setPosition(Vec2(
		m_visibleSize.width / 2,
		m_visibleSize.height / 16 * 15)
	);
	addChild(_label, 3);

	Menu* _menu = Menu::create(
		CreateActionMenu(BUILDING,action_build_path, action_build_selected_path, 0), 
		CreateActionMenu(JUMPING, action_jump_path, action_jump_selected_path, 1),
		CreateActionMenu(MINING, action_mining_path, action_mining_selected_path, 2),
		CreateActionMenu(BLOCKING, action_tpose_path, action_tpose_selected_path, 3),
		CreateActionMenu(EXPLODING, action_explode_path, action_explode_selected_path, 4),
		NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 3);
}

MenuItemImage* MainScene::CreateActionMenu(Actions action, const char* path, const char* selected_path, int id)
{
	MenuItemImage* _action = MenuItemImage::create(
		path,
		selected_path,
		CC_CALLBACK_0(MainScene::CapacityAction, this, action)
	);
	assert(_action);
	_action->setAnchorPoint(Vec2(0, 0.5));
	_action->setScale(0.4);
	_action->setPosition(Vec2(
		m_visibleOrigin.x + 20 + (_action->getContentSize().width * _action->getScale()+20)  * id,
		m_visibleSize.height / 16 * 15)
	);
	return _action;
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
	default:
		break;
	}
}