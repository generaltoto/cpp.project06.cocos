#pragma once

#include "Entities/Lemming.h"

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

	bool onContactBegin(const cocos2d::PhysicsContact &contact) const;

	static void lemmingContactWithWindowBordersCallback(const Lemming*);

	Lemming* getLemmingWithName(const std::string&) const;


    CREATE_FUNC(MainScene)

private:
	std::vector<Lemming*> lemmings;
	std::map<std::string, Lemming*> indexedLemmings;

    cocos2d::Size visibleSize;

	cocos2d::Vec2 visibleOrigin;

	/**
	 * \brief Creates a collision box with the window borders
	 */
	void addWindowsEdgesCollider();

	/**
	 * \brief Creates a Lemming with physics.
	 * \param positionX X Position of the Lemming (cannot be greater than the ScreenWidth)
	 * \param positionY Y Position of the Lemming (cannot be greater than the ScreenHeight)
	 */
	void addLemming(int index, float positionX, float positionY);

};
