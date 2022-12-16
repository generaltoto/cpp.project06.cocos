#pragma once

#include "Entities/Lemming.h"
#include "TileMap/TileMap.h"

class MainScene : public cocos2d::Scene
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
	 * \brief Callback called when a mouse button is clicked
	 * \param event The current event
	 * \return true if we make something of the event
	 */
	bool OnMouseClick(cocos2d::Event *event);

	/**
	 * \brief Callback called when a collision occurs in this scene.
	 * \return true if the collision is acknowledged.
	 */
	bool onContactPreSolve(cocos2d::PhysicsContact&) const;

	/**
	 * \brief Callback called when a collision occurs and has been managed in this scene.
	 * \return true if the collision is acknowledged.
	 */
	bool onContactPostSolve(const cocos2d::PhysicsContact&) const;

	/**
	 * \brief Callback called if the collision concerns a Lemming and the window border or wall.
	 * \param l The concerned lemming.
	 */
	static void lemmingContactWithWindowBordersCallback(Lemming* l);

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

    cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_visibleOrigin;

	void addWindowsEdgesCollider();

	void addLemming(float positionX, float positionY);

	void CreateLemmingSelector();
};
