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
	 * \brief Creates a resume button to go back to the game.
	 * \return The menu item to resume.
	 */
	cocos2d::MenuItemFont* createResumeButton();

	/**
	 * \brief Creates a return button to the main menu scene.
	 * \return The menu item to quit.
	 */
	cocos2d::MenuItemFont* createQuitButton();

	/**
	 * \brief Switches scene to the play one.
	 */
	void resume(cocos2d::Ref*) const;

	/**
	 * \brief Switches scene to the main menu one.
	 */
	void returnMainMenu(cocos2d::Ref*) const;

	/**
	 *brief Creates the menu with all buttons.
	 */
	void CreateDynamicMenu() override;

	CREATE_FUNC(PauseMenu);
};
