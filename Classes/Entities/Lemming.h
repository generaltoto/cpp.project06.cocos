#pragma once

#include "cocos2d.h"
#include "../proj.win32/UtilityFunctions.h"
#include "../proj.win32/Constants.h"

enum LemmingState { SPAWNING, FALLING, WALKING_RIGHT, WALKING_LEFT };

constexpr float spriteScale = 2.0;
constexpr int lemmingSpriteSize = 21;

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
	 * \brief Initiates all members, inherited from cocos.
	 * \return true if succeeded
	 */
	bool init() override;

	/**
	 * \brief Update function inherited from cocos
	 * \param delta ms between each frames
	 */
	void update(float delta) override;

private:

	const float m_lemmingVelocity = 130;

	LemmingState m_currentState;

	int m_currentAcceleration;

	cocos2d::Vec2 m_lemmingSpriteSize;

	cocos2d::Sprite* m_pIdleSpriteFrame;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pFallingSpriteFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pWalkingSpriteFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_pMiningSpriteFrames;

	static void CreateSpriteFrames(Lemming*, const char* filePath);

	static cocos2d::Vector<cocos2d::SpriteFrame*> CreateSpriteFramesFromImage(cocos2d::Vec2 startingPoint, int nbFrames, const char* filePath);

	void Move() const;

	void UpdateMovementStateAndAnimation();

	void RunWithAnimation(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames, bool isFlipped);
};
