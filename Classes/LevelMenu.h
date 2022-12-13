#pragma once

#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"

class LevelMenu : public cocos2d::Scene
{
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   void update(float delta) override;

   // a selector callback
   void menuCloseCallback(cocos2d::Ref* pSender);

   // implement the "static create()" method manually
   CREATE_FUNC(LevelMenu);
};

#endif // __LEVELMENU_SCENE_H__