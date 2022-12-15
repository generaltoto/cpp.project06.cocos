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

   cocos2d::Size _visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 _origin = Director::getInstance()->getVisibleOrigin();

   cocos2d::MenuItemImage* _closeItem = MenuItemImage::create(
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

   m_levelCursor = Sprite::create("map_cursor.png");
   m_levelCursor->setScale(0.3);
   m_levelCursor->setAnchorPoint(Vec2(0.5, 0));
   m_levelCursor->setPosition(Vec2(-20,-20));
   

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

   cocos2d::Sprite* _bg = Sprite::create("map_level.png");
   if (_label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      _bg->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
      _bg->setScale(1.1);
      _bg->setOpacity(200);
      addChild(_bg, 0);
   }

   cocos2d::DrawNode* _draw = DrawNode::create();
   _draw->drawSolidRect(Vec2((_visibleSize.width / 4.5)*3.5, (_visibleSize.height/12)*11), Vec2(_visibleSize.width, (_visibleSize.height / 12) * 2), Color4F(255,255,255,50));
   addChild(_draw, 1);

   cocos2d::MenuItemFont* _lvl1 = MenuItemFont::create("Woods", CC_CALLBACK_1(LevelMenu::selectLevel, this, Vec2((_visibleSize.width / 3), (_visibleSize.height / 4)), 1));
   _lvl1->setPosition(Vec2((_visibleSize.width / 5) * 4.5, (_visibleSize.height / 12) * 10));
   _lvl1->setFontSizeObj(55);

   cocos2d::MenuItemFont* _lvl2 = MenuItemFont::create("Tundra", CC_CALLBACK_1(LevelMenu::selectLevel, this, Vec2((_visibleSize.width / 3), _visibleSize.height/2), 2));
   _lvl2->setPosition(Vec2((_visibleSize.width / 5) * 4.5, (_visibleSize.height / 12) * 9));
   _lvl2->setFontSizeObj(55);

   cocos2d::MenuItemFont* _playButt = MenuItemFont::create("Play", CC_CALLBACK_1(LevelMenu::playLevel, this));
   _playButt->setPosition(Vec2((_visibleSize.width / 5) * 4.5, (_visibleSize.height / 12) * 4));
   _playButt->setFontSizeObj(40);

   cocos2d::MenuItemFont* _menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(LevelMenu::returnToMain, this));
   _menuQuit->setPosition(Vec2((_visibleSize.width / 5) * 4.5, _visibleSize.height/12));
   _menuQuit->setFontSizeObj(40);

   cocos2d::Menu* _menu = Menu::create(_closeItem, _lvl1, _lvl2, _playButt, _menuQuit, NULL);
   _menu->setPosition(Vec2::ZERO);
   addChild(_menu, 1);
   addChild(m_levelCursor, 1);

   return true;
}

void LevelMenu::playLevel(cocos2d::Ref* pSender)
{
   if (m_idLvl != 0) 
   {
      //cocos2d::Scene* _playScene = [Play Scene]::create(m_idlvl);
      //Director::getInstance()->replaceScene(TransitionFade::create(0.5, _playScene, Color3B(255, 255, 255)));
   }
}

void LevelMenu::selectLevel(cocos2d::Ref* pSender, cocos2d::Vec2 coor, int index)
{
   m_levelCursor->setPosition(coor);
   m_idLvl = index;
}

void LevelMenu::returnToMain(cocos2d::Ref* pSender)
{
   Director::getInstance()->popScene();
}

void LevelMenu::update(float delta) { Node::update(delta); }

void LevelMenu::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }