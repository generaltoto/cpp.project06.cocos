#pragma once

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   void update(float delta) override;

   // a selector callback
   void menuCloseCallback(cocos2d::Ref* pSender);

   void Play(Ref* pSender);
   void Settings(Ref* pSender);

   // implement the "static create()" method manually
   CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__