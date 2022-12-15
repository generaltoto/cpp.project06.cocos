#pragma once

#include "cocos2d.h"
#include "../proj.win32/UtilityFunctions.h"
#include "../proj.win32/Constants.h"

enum LemmingState { SPAWNING, FALLING, WALKING };

class Lemming : public cocos2d::Node
{
public:
	/**
	 * \brief Id of this Lemming
	 */
	int m_id{};

	/**
	 * \brief Id of the next Lemming
	 */
	static int m_nextId;

	/**
	 * \brief Current state of the Lemming
	 */
	LemmingState m_currentState;

	/**
	 * \brief Current acceleration of the Lemming. -1 for left and 1 for right.
	 */
	int m_currentAcceleration;

	/**
	 * \brief The Lemming's velocity
	 */
	const float m_lemmingVelocity = 35;

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

	/**
	 * \brief Checks if the Lemming in currently in the air to modify its [currentState]
	 */
	void checkIfFalling();
};