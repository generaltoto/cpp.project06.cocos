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
   

   return true;
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