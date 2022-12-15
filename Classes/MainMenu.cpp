#include "MainMenu.h"
#include "LevelMenu.h"
#include "SettingMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	return create();
}

bool MainMenu::init()
{
	if (!Scene::init()) { return false; }

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	return true;
}

void MainMenu::onEnter()
{
	Scene::onEnter();

	createTitle();
	createBackground();
	createDynamicMenu();
}

void MainMenu::RunPlayScene(cocos2d::Ref* pSender) const
{
	cocos2d::Scene* _levelScene = LevelMenu::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, _levelScene, Color3B(255, 255, 255)));
}

void MainMenu::RunSettingsScene(cocos2d::Ref* pSender) const
{
	cocos2d::Scene* _settingScene = SettingMenu::create();
	Director::getInstance()->pushScene(_settingScene);
}

cocos2d::MenuItemImage* MainMenu::createCloseItem()
{
	cocos2d::MenuItemImage* _closeItem = MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this)
	);
	assert(_closeItem);
	const float x = m_visibleOrigin.x + m_visibleSize.width - _closeItem->getContentSize().width / 2;
	const float y = m_visibleOrigin.y + _closeItem->getContentSize().height / 2;
	_closeItem->setPosition(Vec2(x, y));
	return _closeItem;
}

void MainMenu::createTitle()
{
	cocos2d::Label* _label = Label::createWithTTF("Save the Steves", font_path, 80);
	assert(_label);
	_label->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height - _label->getContentSize().height)
	);
	_label->setTextColor(Color4B(0, 0, 0, 255));
	_label->enableOutline(Color4B(245, 245, 245, 255), 4);
	addChild(_label, 1);
}

void MainMenu::createBackground()
{
	cocos2d::Sprite* _bg = Sprite::create(menu_mainMenu_background_path);
	assert(_bg);
	_bg->setPosition(Vec2(m_visibleSize.width / 2 + m_visibleOrigin.x,
		m_visibleSize.height / 2 + m_visibleOrigin.y)
	);
	_bg->setScale(1.6f);
	addChild(_bg, 0);
}

cocos2d::MenuItemFont* MainMenu::createPlayButton()
{
	cocos2d::MenuItemFont* _menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::RunPlayScene, this));
	_menuPlay->setPosition(Vec2((m_visibleSize.width / 3), (m_visibleSize.height / 3)));
	_menuPlay->setFontSizeObj(69);
	return _menuPlay;
}

cocos2d::MenuItemFont* MainMenu::createSettingsButton()
{
	cocos2d::MenuItemFont* _menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::RunSettingsScene, this));
	_menuSettings->setPosition(Vec2((m_visibleSize.width / 3) * 2, (m_visibleSize.height / 3)));
	_menuSettings->setFontSizeObj(69);
	return _menuSettings;
}

void MainMenu::createDynamicMenu()
{
	cocos2d::Menu* _menu = Menu::create(createCloseItem(), createPlayButton(), createSettingsButton(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}

void MainMenu::update(float delta) { Node::update(delta); }

void MainMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }