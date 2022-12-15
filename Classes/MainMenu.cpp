#include "MainMenu.h"
#include "LevelMenu.h"
#include "SettingMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
   return MainMenu::create();
}

bool MainMenu::init()
{
   if (!Scene::init())
   {
      return false;
   }

   cocos2d::Size _visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 _origin = Director::getInstance()->getVisibleOrigin();

   cocos2d::MenuItemImage* _closeItem = MenuItemImage::create(
      "CloseNormal.png",
      "CloseSelected.png",
      CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

   if (_closeItem == nullptr ||
      _closeItem->getContentSize().width <= 0 ||
      _closeItem->getContentSize().height <= 0)
      throw ERROR_BAD_PATHNAME;
   else
   {
      float x = _origin.x + _visibleSize.width - _closeItem->getContentSize().width / 2;
      float y = _origin.y + _closeItem->getContentSize().height / 2;
      _closeItem->setPosition(Vec2(x, y));
   }

   cocos2d::Label* _label = Label::createWithTTF("Save the Steves", "fonts/Marker Felt.ttf", 80);
   if (_label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _label->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
         _origin.y + _visibleSize.height - _label->getContentSize().height));
      _label->setTextColor(Color4B(0, 0, 0, 255));
      _label->enableOutline(Color4B(245, 245, 245, 255), 4);
      addChild(_label, 1);
   }

   cocos2d::Sprite* _bg = Sprite::create("main_menu.jpg");
   if (_bg == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _bg->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
      _bg->setScale(1.6);
      addChild(_bg, 0);
   }

   cocos2d::MenuItemFont* _menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
   _menuPlay->setPosition(Vec2((_visibleSize.width / 3), (_visibleSize.height / 3)));
   _menuPlay->setFontSizeObj(69);

   cocos2d::MenuItemFont* _menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::Settings, this));
   _menuSettings->setPosition(Vec2((_visibleSize.width / 3) * 2, (_visibleSize.height / 3)));
   _menuSettings->setFontSizeObj(69);

   cocos2d::Menu* _menu = Menu::create(_closeItem, _menuPlay, _menuSettings, NULL);
   _menu->setPosition(Vec2::ZERO);
   addChild(_menu, 1);

   return true;
}

void MainMenu::Play(cocos2d::Ref* pSender)
{
   cocos2d::Scene* _levelScene = LevelMenu::create();
   Director::getInstance()->pushScene(TransitionFade::create(0.5, _levelScene, Color3B(255, 255, 255)));
}

void MainMenu::Settings(cocos2d::Ref* pSender)
{
   cocos2d::Scene* _settingScene = SettingMenu::create();
   Director::getInstance()->pushScene(_settingScene);
}

void MainMenu::update(float delta) { Node::update(delta); }

void MainMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }