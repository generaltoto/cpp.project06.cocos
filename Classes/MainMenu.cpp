#include "MainMenu.h"
#include "LevelMenu.h"

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

   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();


   auto closeItem = MenuItemImage::create(
      "CloseNormal.png",
      "CloseSelected.png",
      CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

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

   auto label = Label::createWithTTF("Save the Steves", "fonts/Marker Felt.ttf", 24);
   if (label == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      label->setPosition(Vec2(origin.x + visibleSize.width / 2,
         origin.y + visibleSize.height - label->getContentSize().height));

      this->addChild(label, 1);
   }

   auto background = Sprite::create("main_menu.jpg");
   if (background == nullptr)
      throw ERROR_BAD_PATHNAME;
   else
   {
      background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
      background->setScale(1.6);

      this->addChild(background, 0);
   }

   auto menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
   menuPlay->setPosition(Vec2((visibleSize.width / 3), (visibleSize.height / 2.5)));

   auto menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::Settings, this));
   menuSettings->setPosition(Vec2((visibleSize.width / 3) * 2, (visibleSize.height / 2.5)));

   auto menu = Menu::create(closeItem, menuPlay, menuSettings, NULL);
   menu->setPosition(Vec2::ZERO);
   this->addChild(menu, 1);

   return true;
}

void MainMenu::Play(cocos2d::Ref* pSender)
{
   auto levelScene = LevelMenu::create();

   // Transition Fade
   Director::getInstance()->replaceScene(TransitionFade::create(0.5, levelScene, Color3B(255, 255, 255)));
}

void MainMenu::Settings(cocos2d::Ref* pSender)
{
   CCLOG("Settings");
}

void MainMenu::update(float delta)
{
   Node::update(delta);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
   //Close the cocos2d-x game scene and quit the application
   Director::getInstance()->end();

   /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

   //EventCustom customEndEvent("game_scene_close_event");
   //_eventDispatcher->dispatchEvent(&customEndEvent);
}