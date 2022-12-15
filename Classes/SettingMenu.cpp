#include "SettingMenu.h"

USING_NS_CC;

Scene* SettingMenu::createScene()
{
   return SettingMenu::create();
}

bool SettingMenu::init()
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
      CC_CALLBACK_1(SettingMenu::menuCloseCallback, this));

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

   cocos2d::MenuItemFont* _menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(SettingMenu::returnToMain, this));
   _menuQuit->setPosition(Vec2((_visibleSize.width / 5) * 4.5, (_visibleSize.height/5)*4.5));
   _menuQuit->setFontSizeObj(40);

   cocos2d::Menu* _menu = Menu::create(_closeItem, _menuQuit, NULL);
   _menu->setPosition(Vec2::ZERO);
   addChild(_menu, 1);

   return true;
}

void SettingMenu::returnToMain(cocos2d::Ref* pSender) 
{
   Director::getInstance()->popScene();
}

void SettingMenu::update(float delta) { Node::update(delta); }

void SettingMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }