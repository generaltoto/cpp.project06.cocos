#pragma once

#include "cocos2d.h"
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

	CREATE_FUNC(MainMenu);

private:

	void CreateDynamicMenu() override;

	MenuItemFont* CreatePlayButton();

	MenuItemFont* CreateSettingsButton();

	void RunPlayScene(Ref*) const;

	void RunSettingsScene(Ref*) const;
};
