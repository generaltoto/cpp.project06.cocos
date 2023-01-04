#pragma once

#include "ModelMenuScene.h"

class SettingMenu : public ModelMenuScene
{
public:
	/**
	 * \brief Executed when we enter the scene. Initializes all components
	 */
	void onEnter() override;

	CREATE_FUNC(SettingMenu);

private:

	void CreateDynamicMenu() override;
};
