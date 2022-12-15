#pragma once

#include "cocos2d.h"
#include "MainScene.h"

class LevelMenu : public cocos2d::Scene
{
public:
	/**
	 * \brief Creates the scene.
	 * \return The created scene.
	 */
	static cocos2d::Scene* createScene();

	/**
	 * \brief Inits the different elements of the scene.
	 * \return True if good init or false if bad init.
	 */
	bool init() override;

	/**
	 * \brief Executed when entering the scene. Creates all the needed components.
	 */
	void onEnter() override;

	/**
	 * \brief Updates the scene with a given time.
	 */
	void update(float) override;

	/**
	 * \brief Closes the window.
	 */
	void closeGameCallback(cocos2d::Ref*);

	/**
	 * \brief Launches a new playing scene with the level index selected.
	 */
	void runLevelScene(cocos2d::Ref*) const;

	/**
	 * \brief Changes the current selected level and updates the cursor on the map.
	 */
	void updateSelectedLevel(cocos2d::Ref*, cocos2d::Vec2, int);

	/**
	 * \brief Changes the scene to return to the main one.
	 */
	void goBackToMenu(cocos2d::Ref*);

	CREATE_FUNC(LevelMenu);

private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;
	cocos2d::Sprite* m_levelCursor;
	int m_idLvl;

	cocos2d::MenuItemImage* createCloseGameButton();

	cocos2d::Sprite* createLevelSelectorCursor();

	void createTitle();

	void createBackground();

	void createSelectionMenu();
};
