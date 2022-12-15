#pragma once

#ifndef __SETTINGMENU_SCENE_H__
#define __SETTINGMENU_SCENE_H__

#include "cocos2d.h"

class SettingMenu : public cocos2d::Scene
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

   /// Changes the scene to return to the main one.
   void returnToMain(cocos2d::Ref*);

   // implement the "static create()" method manually
   CREATE_FUNC(SettingMenu);
};

#endif // __SETTINGMENU_SCENE_H__