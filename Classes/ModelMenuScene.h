#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"

class ModelMenuScene : public cocos2d::Scene
{
public:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	/**
	 * \brief Inits the different elements of the scene.
	 * \return True if good init or false if bad init.
	 */
	bool init() override;

	/**
	 * \brief Updates the scene with a given time.
	 */
	void update(float) override;


	/**
	 * \brief Creates the close button.
	 * \return The menu item to close the window.
	 */
	cocos2d::MenuItemImage* createCloseItem();

	/**
	 * \brief Creates a return button to the last scene.
	 * \return The menu item to go back.
	 */
	cocos2d::MenuItemFont* createReturnButton(cocos2d::Vec2);

	/**
	 * \brief Closes the window.
	 */
	void menuCloseCallback(cocos2d::Ref*);

	/**
	 * \brief Returns to the last scene.
	 */
	void returnToScene(cocos2d::Ref*);

	/**
	 * \brief Creates the game's title on menus.
	 */
	void createTitle();

	/**
	 * \brief Sets the background of the scene with a given path and scale.
	 */
	void createBackground(const char*, float);

	/**
	 * \brief Creates the menu with all buttons.
	 */
	virtual void createDynamicMenu();

	CREATE_FUNC(ModelMenuScene);
};
