#pragma once

#include "ModelMenuScene.h"
#include "MainMenu.h"

class WinMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when entering the scene. Creates all the needed components.
	 */
	void onEnter() override;


	CREATE_FUNC(WinMenu);

private:

	void CreateDynamicMenu() override;

	void setData();

	MenuItemFont* createQuitButton();

	void resume(Ref*) const;

	void returnMainMenu(Ref*) const;
};
