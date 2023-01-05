#include "WinMenu.h"

void WinMenu::onEnter()
{
	Scene::onEnter();

	CreateTitle();
	CreateBackground(menu_mainMenu_background_path, 1.6f);
	CreateDynamicMenu();
	setData();
}

void WinMenu::setData()
{
	std::map<std::string, int>* data = static_cast<std::map<std::string, int>*>(getUserData());

	std::stringstream ss_total;
	ss_total << "TOTAL SPAWNED: " << (*data)["total"];

	Label* total = Label::createWithTTF(ss_total.str(), "fonts/arial.ttf", 40);
	total->setPosition({ m_visibleSize.width / 2, (m_visibleSize.height / 20) * 5 });

	addChild(total, 2);

	std::stringstream ss_ended;
	ss_ended << "TOTAL ENDED: " << (*data)["ended"];

	Label* ended = Label::createWithTTF(ss_ended.str(), "fonts/arial.ttf", 40);
	ended->setPosition({ m_visibleSize.width / 2, (m_visibleSize.height / 20) * 6 });

	addChild(ended, 2);
}

MenuItemFont* WinMenu::createQuitButton()
{
	MenuItemFont* _menuQuit = MenuItemFont::create("Back to main menu", CC_CALLBACK_1(WinMenu::returnMainMenu, this));
	_menuQuit->setPosition(Vec2((m_visibleSize.width / 2), (m_visibleSize.height / 8)));
	_menuQuit->setFontSizeObj(69);
	return _menuQuit;
}

void WinMenu::resume(Ref* pSender) const { Director::getInstance()->popScene(); }

void WinMenu::returnMainMenu(Ref* pSender) const
{
	Scene* _playScene = MainMenu::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
}

void WinMenu::CreateDynamicMenu()
{
	Menu* _menu = Menu::create(createQuitButton(), CreateCloseItem(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}