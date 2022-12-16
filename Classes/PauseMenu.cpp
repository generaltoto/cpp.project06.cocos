#include "PauseMenu.h"

USING_NS_CC;


void PauseMenu::onEnter()
{
	Scene::onEnter();

	createTitle();
	createBackground(menu_mainMenu_background_path, 1.6f);
	createDynamicMenu();
}

cocos2d::MenuItemFont* PauseMenu::createResumeButton()
{
	cocos2d::MenuItemFont* _menuResume = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseMenu::resume, this));
	_menuResume->setPosition(Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 3)));
	_menuResume->setFontSizeObj(69);
	return _menuResume;
}

cocos2d::MenuItemFont* PauseMenu::createQuitButton()
{
	cocos2d::MenuItemFont* _menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(PauseMenu::returnMainMenu, this));
	_menuQuit->setPosition(Vec2((m_visibleSize.width / 3) * 2, (m_visibleSize.height / 3)));
	_menuQuit->setFontSizeObj(69);
	return _menuQuit;
}

void PauseMenu::resume(cocos2d::Ref* pSender) const { cocos2d::Director::getInstance()->popScene(); }

void PauseMenu::returnMainMenu(cocos2d::Ref* pSender) const
{
	cocos2d::Scene* _playScene = MainMenu::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
}

void PauseMenu::createDynamicMenu()
{
	cocos2d::Menu* _menu = Menu::create(createResumeButton(), createQuitButton(), createCloseItem(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}