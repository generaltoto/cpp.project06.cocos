#pragma once

#include "Entities/Lemming.h"
#include "Box2D/Box2D.h"
#include "../proj.win32/Constants.h"

class MainScene : public cocos2d::Layer
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

    CREATE_FUNC(MainScene)

private:
	std::vector<Lemming*> lemmings;

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
	void addLemming(float positionX, float positionY);

	bool onContact(const cocos2d::PhysicsContact &contact);
};
