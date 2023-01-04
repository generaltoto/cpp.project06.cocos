#pragma once

#include "Entities/Lemming.h"
#include "TileMap/TileMap.h"
#include "PauseMenu.h"
#include "ModelMenuScene.h"

enum Actions {MINING, BUILDING, RESET};

class MainScene : public ModelMenuScene
{
public:
	/**
	 * \brief Creates the scene
	 * \return The scene created with physics
	 */
	static cocos2d::Scene* createScene();

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

	/**
	 *brief Creates the menu with all buttons.
	 */
	void createDynamicMenu() override;

	/**
	 * \brief Callback called when a mouse button is clicked
	 * \param event The current event
	 * \return true if we make something of the event
	 */
	bool OnMouseClick(cocos2d::Event *event);

	/**
	 * \brief Callback to be called when we want to take the Left Click event into account.
	 * \param mouseCoordinates The mouse coordinates
	 * \return The selected Lemming
	 */
	Lemming* MouseLeftClickCallBack(cocos2d::Vec2 mouseCoordinates);

	/**
	 * \brief Finds the Lemming corresponding to a given [lemming_name_template] name 
	 * \return The found lemming or nullptr if no Lemming was found.
	 */
	Lemming* getLemmingWithName(const std::string&) const;

    CREATE_FUNC(MainScene)

private:
	TileMap* m_pMap;
	std::vector<Lemming*> m_lemmings;
	std::map<std::string, Lemming*> m_indexedLemmings;
	Lemming* m_pSelectedLemming;
	cocos2d::Sprite* m_pLemmingPointer;
	Actions actionState;

   cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	std::vector<cocos2d::EventKeyboard::KeyCode> keys;

	// DEBUG
	cocos2d::Label* m_mouseText;

	/**
	 * \brief Creates a collision box with the window borders
	 */
	void addWindowsEdgesCollider();

	void addLemming(float positionX, float positionY);

	void CreateLemmingSelector();

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	void capaAction(Actions);
};
