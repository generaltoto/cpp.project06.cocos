#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"
#include "ModelMenuScene.h"
#include "SettingMenu.h"
#include "LevelMenu.h"

class MainMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when entering the scene. Creates all the needed components.
	 */
	void onEnter() override;

	/**
	 * \brief Creates a play button.
	 * \return The menu item to go in the level selection.
	 */
	cocos2d::MenuItemFont* createPlayButton();

	/**
	 * \brief Creates a settings button.
	 * \return The menu item to in the setting menu.
	 */
	cocos2d::MenuItemFont* createSettingsButton();

	/**
	 * \brief Switches scene to the LevelMenu one.
	 */
	void RunPlayScene(cocos2d::Ref*) const;

	/**
	 * \brief Switches scene to the SettingMenu one.
	 */
	void RunSettingsScene(cocos2d::Ref*) const;

	/**
	 *brief Creates the menu with all buttons.
	 */
	void createDynamicMenu() override;

	CREATE_FUNC(MainMenu);
};
