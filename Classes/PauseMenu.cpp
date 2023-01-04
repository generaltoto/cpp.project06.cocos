#include "PauseMenu.h"

void PauseMenu::onEnter()
{
	Scene::onEnter();

	CreateTitle();
	CreateBackground(menu_mainMenu_background_path, 1.6f);
	CreateDynamicMenu();
}

MenuItemFont* PauseMenu::createResumeButton()
{
	MenuItemFont* _menuResume = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseMenu::resume, this));
	_menuResume->setPosition(Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 3)));
	_menuResume->setFontSizeObj(69);
	return _menuResume;
}

MenuItemFont* PauseMenu::createQuitButton()
{
	MenuItemFont* _menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(PauseMenu::returnMainMenu, this));
	_menuQuit->setPosition(Vec2((m_visibleSize.width / 3) * 2, (m_visibleSize.height / 3)));
	_menuQuit->setFontSizeObj(69);
	return _menuQuit;
}

void PauseMenu::resume(Ref* pSender) const { Director::getInstance()->popScene(); }

void PauseMenu::returnMainMenu(Ref* pSender) const
{
	Scene* _playScene = MainMenu::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
}

void PauseMenu::CreateDynamicMenu()
{
	Menu* _menu = Menu::create(createResumeButton(), createQuitButton(), CreateCloseItem(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}