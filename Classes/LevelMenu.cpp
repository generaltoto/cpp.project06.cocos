#include "LevelMenu.h"

USING_NS_CC;

Scene* LevelMenu::createScene() { return create(); }

bool LevelMenu::init()
{
	if (!Scene::init()) return false;

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_levelCursor = createLevelSelectorCursor();
	m_idLvl = 1;

	return true;
}

void LevelMenu::onEnter()
{
	Scene::onEnter();

	createTitle();
	createBackground();
	createSelectionMenu();
}

void LevelMenu::runLevelScene(cocos2d::Ref* pSender) const
{
	if (m_idLvl != 0)
	{
		cocos2d::Scene* _playScene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
	}
}

void LevelMenu::updateSelectedLevel(cocos2d::Ref* pSender, cocos2d::Vec2 coordinates, int index)
{
	m_levelCursor->setPosition(coordinates);
	m_idLvl = index;
}

void LevelMenu::goBackToMenu(cocos2d::Ref* pSender) { Director::getInstance()->popScene(); }

cocos2d::MenuItemImage* LevelMenu::createCloseGameButton()
{
	cocos2d::MenuItemImage* _closeItem = MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_1(LevelMenu::closeGameCallback, this)
	);
	assert(_closeItem);
	const float x = m_visibleOrigin.x + m_visibleSize.width - _closeItem->getContentSize().width / 2;
	const float y = m_visibleOrigin.y + _closeItem->getContentSize().height / 2;
	_closeItem->setPosition(Vec2(x, y));
	return _closeItem;
}

cocos2d::Sprite* LevelMenu::createLevelSelectorCursor()
{
	cocos2d::Sprite* _cursor = Sprite::create(menu_levelMenu_cursor_path);
	assert(_cursor);
	_cursor->setScale(0.3f);
	_cursor->setAnchorPoint(Vec2(0.5, 0));
	_cursor->setPosition(Vec2(-50, -50));
	addChild(_cursor, 1);
	return _cursor;
}

void LevelMenu::createTitle()
{
	cocos2d::Label* _label = Label::createWithTTF("Save the Steves", font_path, 80);
	assert(_label);
	_label->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height - _label->getContentSize().height));
	_label->setTextColor(Color4B(0, 0, 0, 255));
	_label->enableOutline(Color4B(245, 245, 245, 255), 4);
	addChild(_label, 1);
}

void LevelMenu::createBackground()
{
	cocos2d::Sprite* _bg = Sprite::create(menu_levelMenu_background_path);
	assert(_bg);
	_bg->setPosition(Vec2(
		m_visibleSize.width / 2 + m_visibleOrigin.x,
		m_visibleSize.height / 2 + m_visibleOrigin.y)
	);
	_bg->setScale(1.1f);
	_bg->setOpacity(200);
	addChild(_bg, 0);
}

void LevelMenu::createSelectionMenu()
{
	cocos2d::DrawNode* _draw = DrawNode::create();
	_draw->drawSolidRect(
		Vec2((m_visibleSize.width / 4.5) * 3.5, (m_visibleSize.height / 12) * 11),
		Vec2(
			m_visibleSize.width,
			(m_visibleSize.height / 12) * 2), Color4F(255, 255, 255, 50
			)
	);
	addChild(_draw, 1);

	cocos2d::MenuItemFont* _lvl1 = MenuItemFont::create(
		"Woods", 
		CC_CALLBACK_1(
			LevelMenu::updateSelectedLevel,
			this,
			Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 4)), 1
		)
	);
	assert(_lvl1);
	_lvl1->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 10));
	_lvl1->setFontSizeObj(55);

	cocos2d::MenuItemFont* _lvl2 = MenuItemFont::create(
		"Tundra",
		CC_CALLBACK_1(
			LevelMenu::updateSelectedLevel,
			this,
			Vec2((m_visibleSize.width / 3), m_visibleSize.height / 2), 2
		)
	);
	assert(_lvl2);
	_lvl2->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 9));
	_lvl2->setFontSizeObj(55);

	cocos2d::MenuItemFont* _playButt = MenuItemFont::create(
		"Play",
		CC_CALLBACK_1(LevelMenu::runLevelScene, this)
	);
	assert(_playButt);
	_playButt->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 4));
	_playButt->setFontSizeObj(40);

	cocos2d::MenuItemFont* _menuQuit = MenuItemFont::create(
		"Quit",
		CC_CALLBACK_1(LevelMenu::goBackToMenu, this)
	);
	assert(_menuQuit);
	_menuQuit->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, m_visibleSize.height / 12));
	_menuQuit->setFontSizeObj(40);

	cocos2d::Menu* _menu = Menu::create(createCloseGameButton(), _lvl1, _lvl2, _playButt, _menuQuit, NULL);
	assert(_menu);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}

void LevelMenu::update(float delta) { Node::update(delta); }

void LevelMenu::closeGameCallback(Ref* pSender) { Director::getInstance()->end(); }