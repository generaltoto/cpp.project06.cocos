#include "LevelMenu.h"

USING_NS_CC;

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
	createBackground(menu_levelMenu_background_path, 1.1f);
	createDynamicMenu();
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

void LevelMenu::createDynamicMenu()
{
	cocos2d::DrawNode* _draw = cocos2d::DrawNode::create();
	_draw->drawSolidRect(
		cocos2d::Vec2((m_visibleSize.width / 4.5) * 3.5, (m_visibleSize.height / 12) * 11),
		cocos2d::Vec2(
			m_visibleSize.width,
			(m_visibleSize.height / 12) * 2), cocos2d::Color4F(255, 255, 255, 50
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

	cocos2d::Menu* _menu = Menu::create(createCloseItem(), createReturnButton(cocos2d::Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 3)), _lvl1, _lvl2, _playButt, NULL);
	assert(_menu);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}