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

   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();


   auto closeItem = MenuItemImage::create(
      "CloseNormal.png",
      "CloseSelected.png",
      CC_CALLBACK_1(LevelMenu::menuCloseCallback, this));

   if (closeItem == nullptr ||
      closeItem->getContentSize().width <= 0 ||
      closeItem->getContentSize().height <= 0)
      throw ERROR_BAD_PATHNAME;
   else
   {
      float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
      float y = origin.y + closeItem->getContentSize().height / 2;
      closeItem->setPosition(Vec2(x, y));
   }

   // create menu, it's an autorelease object
   this->levelCursor = Sprite::create("map_cursor.png");
   this->levelCursor->setScale(0.3);
   this->setAnchorPoint(Vec2(0.5, 0));

   auto label = Label::createWithTTF("Save the Steves", "fonts/Marker Felt.ttf", 24);
   if (label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      label->setPosition(Vec2(origin.x + visibleSize.width / 2,
         origin.y + visibleSize.height - label->getContentSize().height));
      label->setTextColor(Color4B(0, 0, 0, 255));

      this->addChild(label, 1);
   }

   auto background = Sprite::create("map_level.png");
   if (background == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
      background->setScale(1.1);
      background->setOpacity(200);

      this->addChild(background, 0);
   }

   auto draw = DrawNode::create();
   draw->drawSolidRect(Vec2((visibleSize.width / 4.5)*3.5, visibleSize.height), Vec2(visibleSize.width, visibleSize.height/5), Color4F(255,255,255,50));
   this->addChild(draw, 1);

   auto level1 = MenuItemFont::create("Woods", CC_CALLBACK_1(LevelMenu::SelectLevel, this, Vec2((visibleSize.width / 3), (visibleSize.height / 2.5)), 1));
   level1->setPosition(Vec2((visibleSize.width / 5) * 4.5, visibleSize.height));
   level1->setFontSizeObj(20);

   auto level2 = MenuItemFont::create("Tundra", CC_CALLBACK_1(LevelMenu::SelectLevel, this, Vec2((visibleSize.width / 3), visibleSize.height), 1));
   level2->setPosition(Vec2((visibleSize.width / 5) * 4.5, visibleSize.height/2));
   level2->setFontSizeObj(20);

   auto menu = Menu::create(closeItem, level1, level2, NULL);
   menu->setPosition(Vec2::ZERO);
   this->addChild(menu, 1);
   this->addChild(levelCursor, 1);
   CCLOG("%f    %f", visibleSize.width, visibleSize.height);

   return true;
}

void LevelMenu::PlayLevel(cocos2d::Ref* pSender, int level)
{

}

void LevelMenu::SelectLevel(cocos2d::Ref* pSender, cocos2d::Vec2 coor, int index)
{
   this->levelCursor->setPosition(coor);
   this->indexLevel = index;

}


void LevelMenu::update(float delta)
{
   Node::update(delta);
}

void LevelMenu::menuCloseCallback(Ref* pSender)
{
   //Close the cocos2d-x game scene and quit the application
   Director::getInstance()->end();

   /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

   //EventCustom customEndEvent("game_scene_close_event");
   //_eventDispatcher->dispatchEvent(&customEndEvent);
}