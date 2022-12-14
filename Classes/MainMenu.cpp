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

   auto _visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 _origin = Director::getInstance()->getVisibleOrigin();

   auto _closeItem = MenuItemImage::create(
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

   auto _label = Label::createWithTTF("Save the Steves", "fonts/Marker Felt.ttf", 24);
   if (_label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _label->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
         _origin.y + _visibleSize.height - _label->getContentSize().height));
      this->addChild(_label, 1);
   }

   auto _bg = Sprite::create("main_menu.jpg");
   if (_bg == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _bg->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
      _bg->setScale(1.6);
      this->addChild(_bg, 0);
   }

   auto _menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
   _menuPlay->setPosition(Vec2((_visibleSize.width / 3), (_visibleSize.height / 2.5)));

   auto _menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::Settings, this));
   _menuSettings->setPosition(Vec2((_visibleSize.width / 3) * 2, (_visibleSize.height / 2.5)));

   auto _menu = Menu::create(_closeItem, _menuPlay, _menuSettings, NULL);
   _menu->setPosition(Vec2::ZERO);
   this->addChild(_menu, 1);

   return true;
}

void MainMenu::Play(cocos2d::Ref* pSender)
{
   auto _levelScene = LevelMenu::create();
   Director::getInstance()->pushScene(TransitionFade::create(0.5, _levelScene, Color3B(255, 255, 255)));
}

void MainMenu::Settings(cocos2d::Ref* pSender)
{
   auto _settingScene = SettingMenu::create();
   Director::getInstance()->pushScene(_settingScene);
}

void MainMenu::update(float delta) { Node::update(delta); }

void MainMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }