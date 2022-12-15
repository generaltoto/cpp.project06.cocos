#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"

class MainMenu : public cocos2d::Scene
{
public:
	/**
	 * \brief Creates the scenes.
	 * \return The create Scene.
	 */
	static cocos2d::Scene* createScene();

	/**
	 * \brief Inits the different elements of the scene.
	 * \return True if good init or false if bad init.
	 */
	bool init() override;

	void onEnter() override;

	/**
	 * \brief Updates the scene with a given time.
	 */
	void update(float) override;

	/**
	 * \brief Closes the window.
	 */
	void menuCloseCallback(cocos2d::Ref*);

	/**
	 * \brief Switches scene to the LevelMenu one.
	 */
	void RunPlayScene(cocos2d::Ref*) const;

	/**
	 * \brief Switches scene to the SettingMenu one.
	 */
	void RunSettingsScene(cocos2d::Ref*) const;

	CREATE_FUNC(MainMenu);

private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	cocos2d::MenuItemImage* createCloseItem();

	void createTitle();

	void createBackground();

	cocos2d::MenuItemFont* createPlayButton();

	cocos2d::MenuItemFont* createSettingsButton();

	void createDynamicMenu();
};
