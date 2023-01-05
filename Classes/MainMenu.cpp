#include "MainMenu.h"

USING_NS_CC;


void MainMenu::onEnter()
{
	Scene::onEnter();

	CreateTitle();
	CreateBackground(menu_mainMenu_background_path, 1.6f);
	CreateDynamicMenu();
}

MenuItemFont* MainMenu::CreatePlayButton()
{
	MenuItemFont* _menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::RunPlayScene, this));
	_menuPlay->setPosition(Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 3)));
	_menuPlay->setFontSizeObj(69);
	return _menuPlay;
}

MenuItemFont* MainMenu::CreateSettingsButton()
{
	MenuItemFont* _menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::RunSettingsScene, this));
	_menuSettings->setPosition(Vec2((m_visibleSize.width / 3) * 2, (m_visibleSize.height / 3)));
	_menuSettings->setFontSizeObj(69);
	return _menuSettings;
}

void MainMenu::RunPlayScene(Ref* pSender) 
{
	//ModelMenuScene::PlayMenuSoundEffect();
	Scene* _levelScene = LevelMenu::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, _levelScene, Color3B(255, 255, 255)));
}

void MainMenu::RunSettingsScene(Ref* pSender)
{
	//ModelMenuScene::PlayMenuSoundEffect();
	Scene* _settingScene = SettingMenu::create();
	Director::getInstance()->pushScene(_settingScene);
}

void MainMenu::CreateDynamicMenu()
{
	Menu* _menu = Menu::create(CreateCloseItem(), CreatePlayButton(), CreateSettingsButton(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}