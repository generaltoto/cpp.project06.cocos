#pragma once

#include "../proj.win32/Constants.h"

class SettingMenu : public cocos2d::Scene
{
public:
	/**
	 * \brief Creates the scenes.
	 * \return The created scene.
	 */
	static cocos2d::Scene* createScene();

	/**
	 * \brief Inits the different elements of the scene.
	 * \return True if initialized correctly, False if not.
	 */
	bool init() override;

	/**
	 * \brief Executed when we enter the scene. Initializes all components
	 */
	void onEnter() override;

	/**
	 * \brief Updates the scene with a given time.
	 */
	void update(float) override;

	/**
	 * \brief Changes the scene to return to the main one.
	 */
	void returnToMain(cocos2d::Ref*);

	CREATE_FUNC(SettingMenu);

private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	cocos2d::MenuItemImage* createCloseButton();

	void menuCloseCallback(cocos2d::Ref*);

	void createTitle();

	void createBackground();

	cocos2d::MenuItemFont* createBackToMainButton();

	void createDynamicMenu();
};
