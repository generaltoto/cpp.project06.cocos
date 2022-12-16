#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"
#include "ModelMenuScene.h"
#include "MainMenu.h"

class PauseMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when entering the scene. Creates all the needed components.
	 */
	void onEnter() override;

	/**
 * \brief Switches scene to the LevelMenu one.
 */
	void resume(cocos2d::Ref*) const;

	/**
	 * \brief Switches scene to the SettingMenu one.
	 */
	void returnMainMenu(cocos2d::Ref*) const;

	void createDynamicMenu() override;

	CREATE_FUNC(PauseMenu);

private:
	cocos2d::MenuItemFont* createResumeButton();

	cocos2d::MenuItemFont* createQuitButton();
};
