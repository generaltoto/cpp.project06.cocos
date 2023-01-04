#pragma once

#include "Entities/Lemming.h"
#include "TileMap/TileMap.h"
#include "PauseMenu.h"
#include "ModelMenuScene.h"

enum Actions { MINING, BUILDING, RESET };

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
	bool m_loaded;
	time_t m_nextSpawn;

	TileMap* m_pMap{};
	std::vector<Lemming*> m_lemmings;
	Lemming* m_pSelectedLemming{};
	Sprite* m_pLemmingPointer{};
	Actions actionState;

	void CreateDynamicMenu() override;

	void AddWindowsEdgesCollider();

	void AddLemming(float positionX, float positionY);

	void CreateLemmingSelector();

	bool OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool OnMouseClick(Event* event);

	bool MouseLeftClickCallBack(Vec2 mouseCoordinates);

	void CapacityAction(Actions);
};
