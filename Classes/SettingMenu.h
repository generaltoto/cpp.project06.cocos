#pragma once

#include "../proj.win32/Constants.h"
#include "ModelMenuScene.h"

class SettingMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when we enter the scene. Initializes all components
	 */
	void onEnter() override;

	/**
	 *brief Creates the menu with all buttons.
	 */
	void createDynamicMenu() override;

	CREATE_FUNC(SettingMenu);
};
