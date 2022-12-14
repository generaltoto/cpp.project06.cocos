#include "LevelMenu.h"

USING_NS_CC;

Scene* LevelMenu::createScene()
{
   return LevelMenu::create();
}

bool LevelMenu::init()
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
      CC_CALLBACK_1(LevelMenu::menuCloseCallback, this));

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

   this->_levelCursor = Sprite::create("map_cursor.png");
   this->_levelCursor->setScale(0.3);
   this->setAnchorPoint(Vec2(0.5, 0));

   auto _label = Label::createWithTTF("Save the Steves", "fonts/Marker Felt.ttf", 24);
   if (_label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _label->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
         _origin.y + _visibleSize.height - _label->getContentSize().height));
      _label->setTextColor(Color4B(0, 0, 0, 255));
      this->addChild(_label, 1);
   }

   auto _bg = Sprite::create("map_level.png");
   if (_label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _bg->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
      _bg->setScale(1.1);
      _bg->setOpacity(200);
      this->addChild(_bg, 0);
   }

   auto _draw = DrawNode::create();
   _draw->drawSolidRect(Vec2((_visibleSize.width / 4.5)*3.5, _visibleSize.height), Vec2(_visibleSize.width, _visibleSize.height/5), Color4F(255,255,255,50));
   this->addChild(_draw, 1);

   auto _lvl1 = MenuItemFont::create("Woods", CC_CALLBACK_1(LevelMenu::selectLevel, this, Vec2((_visibleSize.width / 3), (_visibleSize.height / 2.5)), 1));
   _lvl1->setPosition(Vec2((_visibleSize.width / 5) * 4.5, _visibleSize.height));
   _lvl1->setFontSizeObj(20);

   auto _lvl2 = MenuItemFont::create("Tundra", CC_CALLBACK_1(LevelMenu::selectLevel, this, Vec2((_visibleSize.width / 3), _visibleSize.height), 1));
   _lvl2->setPosition(Vec2((_visibleSize.width / 5) * 4.5, _visibleSize.height/2));
   _lvl2->setFontSizeObj(20);

   auto _menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(LevelMenu::returnToMain, this));
   _menuQuit->setPosition(Vec2((_visibleSize.width / 5) * 4.5, _origin.y + +_menuQuit->getContentSize().height / 2));
   _menuQuit->setFontSizeObj(15);

   auto _menu = Menu::create(_closeItem, _lvl1, _lvl2, _menuQuit, NULL);
   _menu->setPosition(Vec2::ZERO);
   this->addChild(_menu, 1);
   this->addChild(_levelCursor, 1);

   CCLOG("%f    %f", _visibleSize.width, _visibleSize.height);

   return true;
}

void LevelMenu::playLevel(cocos2d::Ref* pSender, int level)
{
   //to edit
}

void LevelMenu::selectLevel(cocos2d::Ref* pSender, cocos2d::Vec2 coor, int index)
{
   this->_levelCursor->setPosition(coor);
   this->_idLevel = index;
}

void LevelMenu::returnToMain(cocos2d::Ref* pSender)
{
   Director::getInstance()->popScene();
}

void LevelMenu::update(float delta) { Node::update(delta); }

void LevelMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }