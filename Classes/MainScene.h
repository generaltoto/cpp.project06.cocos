#pragma once

#include "Entities/Lemming.h"
#include "TileMap/TileMap.h"
#include "PauseMenu.h"
#include "WinMenu.h"
#include "ModelMenuScene.h"

class MainScene : public ModelMenuScene
{
public:
	/**
	 * \brief Creates the scene
	 * \return The scene created with physics
	 */
	static Scene* createScene();

	/**
	 * \brief Initiates all members
	 * \return true if succeeded
	 */
	bool init() override;

	/**
	 * \brief Loads everything into the scene
	 */
	void onEnter() override;

	/**
	 * \brief Function called in the game loop
	 * \param delta advancement in the framerate render
	 */
	void update(float delta) override;

	CREATE_FUNC(MainScene)

private:
	bool m_loaded{};
	time_t m_nextSpawn{};
	int lemCount;
	Label* countDisp;
	time_t timerStart;
	Label* timerDisp;

	TileMap* m_pMap{};

	std::vector<Lemming*> m_lemmings;
	Lemming* m_pSelectedLemming{};
	Lemming* m_pPreviousSelectedLemming{};
	Sprite* m_pLemmingPointer{};

	int m_totalLemmings = 3;
	int m_lemmingsSpawned = 0;
	int m_lemmingsEnded = 0;

	void CreateDynamicMenu() override;

	MenuItemImage* CreateActionMenu(LemmingActionState, const char*, const char*, int);

	void AddWindowsEdgesCollider();

	void SpawnLemmings();

	void AddLemming(float positionX, float positionY);

	bool OnLemmingContactBegin(const PhysicsContact& contact);

	void UpdatePreviousSelectedLemming();

	void UpdateLemmingCursorPos() const;

	void UpdateSelectedLemmingActionState(LemmingActionState state);

	void CreateLemmingSelector();

	bool OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool OnMouseClick(Event* event);

	bool MouseLeftClickCallBack(Vec2 mouseCoordinates);
};
