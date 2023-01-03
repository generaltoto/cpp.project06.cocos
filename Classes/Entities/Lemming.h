#pragma once

#include "cocos2d.h"
#include "../proj.win32/UtilityFunctions.h"
#include "../proj.win32/Constants.h"

enum LemmingState { SPAWNING, FALLING, WALKING };

const float spriteScale = 3.0;
const int lemmingSpriteSize = 21;

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
	const float m_lemmingVelocity = 10;

	/**
	 * \brief Get the lemming's sprite size
	 * \return A vector with the sprite size (x for width and y for height)
	 */
	cocos2d::Vec2 getSpriteSize() const { return m_lemmingSpriteSize; }

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

	void update(float delta) override;

	/**
	 * \brief Checks if the Lemming in currently in the air to modify its [currentState]
	 */
	void checkIfFalling();

private:

	cocos2d::Vec2 m_lemmingSpriteSize;

	cocos2d::Sprite* m_pIdleSpriteFrame;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pFallingSpriteFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pWalkingSpriteFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pMiningSpriteFrames;

	static void CreateSpriteFrames(Lemming*, const char* filePath);

	static cocos2d::Vector<cocos2d::SpriteFrame*> CreateSpriteFramesFromImage(
		cocos2d::Vec2 startingPoint,
		int nbFrames,
		const char* filePath
	);

	void RunWithAnimation(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames);
};
