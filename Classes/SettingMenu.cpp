#include "SettingMenu.h"

void SettingMenu::onEnter()
{
	Scene::onEnter();

	CreateTitle();
	CreateBackground(menu_mainMenu_background_path, 1.6f);
	CreateDynamicMenu();
}

void SettingMenu::CreateDynamicMenu()
{
	Menu* _menu = Menu::create(CreateCloseItem(), CreateReturnButton(Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 5) * 4.5)), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}