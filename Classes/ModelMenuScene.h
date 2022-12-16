#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"

class ModelMenuScene : public cocos2d::Scene
{
public:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	/**
	 * \brief Creates the scenes.
	 * \return The create Scene.
	 */
	static cocos2d::Scene* createScene();

	/**
	 * \brief Creates the close button.
	 * \return The menu item to close the window.
	 */
	cocos2d::MenuItemImage* createCloseItem();

	cocos2d::MenuItemFont* createReturnButton(cocos2d::Vec2);

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
	 * \brief Closes the window.
	 */
	void menuCloseCallback(cocos2d::Ref*);

	void returnToScene(cocos2d::Ref*);

	virtual void createDynamicMenu();

	void createTitle();

	void createBackground(const char*, float);

	CREATE_FUNC(ModelMenuScene);
};
