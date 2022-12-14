#pragma once

#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"

class LevelMenu : public cocos2d::Scene
{
private:
   cocos2d::Sprite* _levelCursor;
   int _idLevel;

public:
   /// Creates the scene.
   static cocos2d::Scene* createScene();

   /// Inits the different elements of the scene.
   virtual bool init();

   /// Updates the scene with a given time.
   void update(float) override;

   /// Closes the window.
   void menuCloseCallback(cocos2d::Ref*);

   /// Lunchs a new playing scene with a given level index.
   void playLevel(cocos2d::Ref*, int);

   /// Changes the current selected level and updates the cursor on the map.
   void selectLevel(cocos2d::Ref*, cocos2d::Vec2, int);

   void returnToMain(cocos2d::Ref*);

   // implement the "static create()" method manually
   CREATE_FUNC(LevelMenu);
};

#endif // __LEVELMENU_SCENE_H__