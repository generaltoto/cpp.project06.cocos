#include "SettingMenu.h"

cocos2d::Scene* SettingMenu::createScene() { return create(); }

bool SettingMenu::init()
{
	if (!Scene::init()) return false;

	m_visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	m_visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();

	return true;
}

void SettingMenu::onEnter()
{
	Scene::onEnter();

	createTitle();
	createBackground();
	createDynamicMenu();
}

void SettingMenu::returnToMain(cocos2d::Ref* pSender) { cocos2d::Director::getInstance()->popScene(); }

cocos2d::MenuItemImage* SettingMenu::createCloseButton()
{
	cocos2d::MenuItemImage* _closeItem = cocos2d::MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_1(SettingMenu::menuCloseCallback, this)
	);
	assert(_closeItem);
	const float x = m_visibleOrigin.x + m_visibleSize.width - _closeItem->getContentSize().width / 2;
	const float y = m_visibleOrigin.y + _closeItem->getContentSize().height / 2;
	_closeItem->setPosition(cocos2d::Vec2(x, y));
	return _closeItem;
}

void SettingMenu::createTitle()
{
	cocos2d::Label* _label = cocos2d::Label::createWithTTF("Save the Steves", font_path, 80);
	assert(_label);
	_label->setPosition(cocos2d::Vec2(m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height - _label->getContentSize().height)
	);
	_label->setTextColor(cocos2d::Color4B(0, 0, 0, 255));
	_label->enableOutline(cocos2d::Color4B(245, 245, 245, 255), 4);
	addChild(_label, 1);
}

void SettingMenu::createBackground()
{
	cocos2d::Sprite* _bg = cocos2d::Sprite::create(menu_mainMenu_background_path);
	assert(_bg);
	_bg->setPosition(cocos2d::Vec2(m_visibleSize.width / 2 + m_visibleOrigin.x,
		m_visibleSize.height / 2 + m_visibleOrigin.y)
	);
	_bg->setScale(1.6f);
	addChild(_bg, 0);
}

cocos2d::MenuItemFont* SettingMenu::createBackToMainButton()
{
	cocos2d::MenuItemFont* _menuQuit = cocos2d::MenuItemFont::create(
		"Quit",
		CC_CALLBACK_1(SettingMenu::returnToMain, this)
	);
	_menuQuit->setPosition(cocos2d::Vec2((m_visibleSize.width / 5) * 4.5, (m_visibleSize.height / 5) * 4.5));
	_menuQuit->setFontSizeObj(40);
	return _menuQuit;
}

void SettingMenu::createDynamicMenu()
{
	cocos2d::Menu* _menu = cocos2d::Menu::create(createCloseButton(), createBackToMainButton(), NULL);
	_menu->setPosition(cocos2d::Vec2::ZERO);
	addChild(_menu, 1);
}

void SettingMenu::update(float delta) { Node::update(delta); }

void SettingMenu::menuCloseCallback(Ref* pSender) { cocos2d::Director::getInstance()->end(); }