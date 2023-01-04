#pragma once

#include "cocos2d.h"
#include "ModelMenuScene.h"
#include "MainScene.h"

class LevelMenu : public ModelMenuScene
{
public:
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
	 * \brief Launches a new playing scene with the level index selected.
	 */
	void runLevelScene(cocos2d::Ref*) const;

	/**
	 * \brief Creates the level cursor to see the level selected.
	 * \return The sprite of the level selector.
	 */
	cocos2d::Sprite* createLevelSelectorCursor();

	/**
	 * \brief Changes the current selected level and updates the cursor on the map.
	 */
	void updateSelectedLevel(cocos2d::Ref*, cocos2d::Vec2, int);

	/**
	 *brief Creates the menu with all buttons.
	 */
	void CreateDynamicMenu() override;

	CREATE_FUNC(LevelMenu);

private:
	cocos2d::Sprite* m_levelCursor;
	int m_idLvl;
};
