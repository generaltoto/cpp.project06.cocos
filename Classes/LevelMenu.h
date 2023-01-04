#pragma once

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

	CREATE_FUNC(LevelMenu);

private:
	Sprite* m_levelCursor;
	int m_idLvl;

	void CreateDynamicMenu() override;

	void RunLevelScene(Ref*) const;

	Sprite* CreateLevelSelectorCursor();

	void UpdateSelectedLevel(Ref*, Vec2, int);
};
