#pragma once

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
   /// Creates the scenes.
   static cocos2d::Scene* createScene();

   /// Inits the different elements of the scene.
   virtual bool init();

   /// Updates the scene with a given time.
   void update(float) override;

   /// Closes the window.
   void menuCloseCallback(cocos2d::Ref*);

   /// Switchs scene to the LevelMenu one.
   void Play(cocos2d::Ref*);

   /// Switchs scene to the SettingMenu one.
   void Settings(cocos2d::Ref*);

   // implement the "static create()" method manually
   CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__