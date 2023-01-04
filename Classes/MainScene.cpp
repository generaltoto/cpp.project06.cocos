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

	const Vec2 _middleScreen = { m_visibleSize.width / 2, m_visibleSize.height / 2 };
	for (int i = 0; i < 3; i++) AddLemming(_middleScreen.x + (300.f * i), _middleScreen.y);
	m_pSelectedLemming = m_lemmings[0];
	CreateLemmingSelector();

	AddWindowsEdgesCollider();
	CreateDynamicMenu();

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

void MainScene::update(float delta)
{
	Node::update(delta);

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
		Vec2(
			0,
			0
		),
		Vec2(
			m_visibleSize.width,
			m_visibleSize.height / 7
		),
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


bool MainScene::OnMouseClick(Event* event)
{
	const auto* _mouseEvent = dynamic_cast<EventMouse*>(event);

	const Vec2 _cursorPos = { _mouseEvent->getCursorX(), _mouseEvent->getCursorY() };

	if (_mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		m_pSelectedLemming = MouseLeftClickCallBack(_cursorPos);

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
	_body->setName(window_collision_name_template);

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
	m_indexedLemmings.insert(std::make_pair(_l->getName(), _l));
}

void MainScene::CreateLemmingSelector()
{
	Sprite* _sp = Sprite::create(lemming_selector_asset_path);
	assert(_sp);
	const Vec2 _targetLemmingPos = m_pSelectedLemming->getPosition();
	const Vec2 _targetLemmingSize = m_pSelectedLemming->getSpriteSize();
	_sp->setPosition({
		_targetLemmingPos.x, _targetLemmingPos.y
		});
	m_pLemmingPointer = _sp;
	m_pLemmingPointer->setVisible(false);
	addChild(m_pLemmingPointer);
}

Lemming* MainScene::MouseLeftClickCallBack(Vec2 mouseCoordinates)
{
	for (Lemming*& _l : m_lemmings)
	{
		if (_l->getPhysicsBody()->getShape(0)->containsPoint(mouseCoordinates))
		{
			m_pLemmingPointer->setVisible(true);
			return _l;
		}
	}
	return nullptr;
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