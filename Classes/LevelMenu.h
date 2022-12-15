#pragma once

#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"
#include "MainScene.h"

class LevelMenu : public cocos2d::Scene
{
private:
   cocos2d::Sprite* m_levelCursor;
   int m_idLvl;

public:
   /// Creates the scene.
   static cocos2d::Scene* createScene();

   /// Inits the different elements of the scene.
   virtual bool init();

   /// Updates the scene with a given time.
   void update(float) override;

   /// Closes the window.
   void menuCloseCallback(cocos2d::Ref*);

   /// Lunchs a new playing scene with the level index selected.
   void playLevel(cocos2d::Ref*);

   /// Changes the current selected level and updates the cursor on the map.
   void selectLevel(cocos2d::Ref*, cocos2d::Vec2, int);

   /// Changes the scene to return to the main one.
   void returnToMain(cocos2d::Ref*);

   // implement the "static create()" method manually
   CREATE_FUNC(LevelMenu);
};

#endif // __LEVELMENU_SCENE_H__