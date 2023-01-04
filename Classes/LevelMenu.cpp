#include "LevelMenu.h"

USING_NS_CC;

bool LevelMenu::init()
{
	if (!ModelMenuScene::init()) return false;

	m_levelCursor = CreateLevelSelectorCursor();
	m_idLvl = 0;

	return true;
}

void LevelMenu::onEnter()
{
	Scene::onEnter();

	CreateTitle();
	CreateBackground(menu_levelMenu_background_path, 1.1f);
	CreateDynamicMenu();
}

void LevelMenu::RunLevelScene(Ref* pSender) const
{
	if (m_idLvl != 0)
	{
		Scene* _playScene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
	}
}

void LevelMenu::UpdateSelectedLevel(Ref* pSender, Vec2 coordinates, int index)
{
	m_levelCursor->setPosition(coordinates);
	m_idLvl = index;
}

Sprite* LevelMenu::CreateLevelSelectorCursor()
{
	Sprite* _cursor = Sprite::create(menu_levelMenu_cursor_path);
	assert(_cursor);
	_cursor->setScale(0.3f);
	_cursor->setAnchorPoint(Vec2(0.5, 0));
	_cursor->setPosition(Vec2(-50, -50));
	addChild(_cursor, 1);
	return _cursor;
}

void LevelMenu::CreateDynamicMenu()
{
	DrawNode* _draw = DrawNode::create();
	_draw->drawSolidRect(
		Vec2((m_visibleSize.width / 4.5) * 3.5, (m_visibleSize.height / 12) * 11),
		Vec2(
			m_visibleSize.width,
			(m_visibleSize.height / 12) * 2), Color4F(255, 255, 255, 50
			)
	);
	addChild(_draw, 1);

	MenuItemFont* _lvl1 = MenuItemFont::create(
		"Woods", 
		CC_CALLBACK_1(
			LevelMenu::UpdateSelectedLevel,
			this,
			Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 4)), 1
		)
	);
	assert(_lvl1);
	_lvl1->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 10));
	_lvl1->setFontSizeObj(55);

	MenuItemFont* _lvl2 = MenuItemFont::create(
		"Tundra",
		CC_CALLBACK_1(
			LevelMenu::UpdateSelectedLevel,
			this,
			Vec2((m_visibleSize.width / 3), m_visibleSize.height / 2), 2
		)
	);
	assert(_lvl2);
	_lvl2->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 9));
	_lvl2->setFontSizeObj(55);

	MenuItemFont* _playButt = MenuItemFont::create(
		"Play",
		CC_CALLBACK_1(LevelMenu::RunLevelScene, this)
	);
	assert(_playButt);
	_playButt->setPosition(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 4));
	_playButt->setFontSizeObj(40);

	Menu* _menu = Menu::create(CreateCloseItem(), CreateReturnButton(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 12) * 3)), _lvl1, _lvl2, _playButt, NULL);
	assert(_menu);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}