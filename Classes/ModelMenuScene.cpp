#include "MainMenu.h"
#include "LevelMenu.h"
#include "SettingMenu.h"

USING_NS_CC;

Scene* ModelMenuScene::createScene()
{
	return create();
}

bool ModelMenuScene::init()
{
	if (!Scene::init()) { return false; }

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	return true;
}

cocos2d::MenuItemImage* ModelMenuScene::createCloseItem()
{
	cocos2d::MenuItemImage* _closeItem = MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_1(ModelMenuScene::menuCloseCallback, this)
	);
	assert(_closeItem);
	const float x = m_visibleOrigin.x + m_visibleSize.width - _closeItem->getContentSize().width / 2;
	const float y = m_visibleOrigin.y + _closeItem->getContentSize().height / 2;
	_closeItem->setPosition(Vec2(x, y));
	return _closeItem;
}

cocos2d::MenuItemFont* ModelMenuScene::createReturnButton(cocos2d::Vec2 position)
{
	cocos2d::MenuItemFont* _menuQuit = cocos2d::MenuItemFont::create(
		"Quit",
		CC_CALLBACK_1(ModelMenuScene::returnToScene, this)
	);
	_menuQuit->setPosition(position);
	_menuQuit->setFontSizeObj(40);
	return _menuQuit;
}

void ModelMenuScene::createTitle()
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

void ModelMenuScene::createBackground(const char* path, float scale)
{
	cocos2d::Sprite* _bg = Sprite::create(path);
	assert(_bg);
	_bg->setPosition(Vec2(m_visibleSize.width / 2 + m_visibleOrigin.x,
		m_visibleSize.height / 2 + m_visibleOrigin.y)
	);
	_bg->setScale(scale);
	addChild(_bg, 0);
}

void ModelMenuScene::createDynamicMenu()
{
	cocos2d::Menu* _menu = cocos2d::Menu::create(createCloseItem(), NULL);
	_menu->setPosition(cocos2d::Vec2::ZERO);
	addChild(_menu, 1);
}

void ModelMenuScene::returnToScene(cocos2d::Ref* pSender) { cocos2d::Director::getInstance()->popScene(); }

void ModelMenuScene::update(float delta) { Node::update(delta); }

void ModelMenuScene::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }