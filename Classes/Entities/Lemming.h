#pragma once

#include "cocos2d.h"
#include "../proj.win32/Constants.h"

class Lemming : public cocos2d::Node
{
public:
	/**
	 * \brief Creates the lemming
	 * \return The sprite created with physic body
	 */
	static Lemming* create(const char* filePath, cocos2d::Vec2 pos);

	/**
	 * \brief Initiates all members
	 * \return true if succeeded
	 */
	bool init() override;

	cocos2d::Sprite* sprite;

	const float lemmingVelocity = 75;

	void updateVelocity(float delta, cocos2d::Size vSize, cocos2d::Vec2 vOrigin, float platformHeight);
};
