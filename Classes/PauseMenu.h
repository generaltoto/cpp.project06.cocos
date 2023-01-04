#pragma once

#include "ModelMenuScene.h"
#include "MainMenu.h"

class PauseMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when entering the scene. Creates all the needed components.
	 */
	void onEnter() override;

	CREATE_FUNC(PauseMenu);

private:

	void CreateDynamicMenu() override;

	MenuItemFont* createResumeButton();

	MenuItemFont* createQuitButton();

	void resume(Ref*) const;

	void returnMainMenu(Ref*) const;
};
