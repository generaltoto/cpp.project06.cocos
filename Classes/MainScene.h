#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MainScene : public cocos2d::Layer
{
public:
	MainScene();

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

	void update(float delta) override;

    CREATE_FUNC(MainScene)

private:
    cocos2d::Sprite *spLemming;

    cocos2d::Size visibleSize;

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
};

#endif // __HELLOWORLD_SCENE_H__
