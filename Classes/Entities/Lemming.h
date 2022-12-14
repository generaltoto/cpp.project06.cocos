#pragma once

#include "cocos2d.h"
#include "../proj.win32/UtilityFunctions.h"
#include "../proj.win32/Constants.h"

enum LemmingState { SPAWNING, FALLING, WALKING };

class Lemming : public cocos2d::Node
{
public:
	int id{};
	static int nextId;

	LemmingState currentState;

	int currentAcceleration;

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

	const float lemmingVelocity = 50;

	void updateForces(float delta, float platformHeight);
};
