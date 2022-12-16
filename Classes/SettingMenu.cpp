#include "SettingMenu.h"

void SettingMenu::onEnter()
{
	Scene::onEnter();

	createTitle();
	createBackground(menu_mainMenu_background_path, 1.6f);
	createDynamicMenu();
}

void SettingMenu::createDynamicMenu()
{
	cocos2d::Menu* _menu = cocos2d::Menu::create(createCloseItem(), createReturnButton(cocos2d::Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 5) * 4.5)), NULL);
	_menu->setPosition(cocos2d::Vec2::ZERO);
	addChild(_menu, 1);
}