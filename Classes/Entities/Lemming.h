#pragma once

#include "math/Vec2.h"
#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "../proj.win32/UtilityFunctions.h"
#include "../proj.win32/Paths.h"
#include "../proj.win32/Bitmasks.h"

USING_NS_CC;

enum LemmingState { SPAWNING, FALLING, WALKING_RIGHT, WALKING_LEFT };

enum LemmingActionState { CHILLING, MINING, BUILDING, BLOCKING, JUMPING, EXPLODING };

constexpr float spriteScale = 2.0;
constexpr int lemmingSpriteSize = 21;

class Lemming : public Node
{
public:

	/** \brief Id of this Lemming */
	int m_id{};

	/** \brief Id of the next Lemming */
	static int m_nextId;

	/**
	 * \brief Creates the lemming
	 * \return The sprite created with physic body
	 */
	static Lemming* create(const char* filePath, ::Vec2 pos);

	void UpdateActionState(LemmingActionState action);

	/**
	 * \brief Get the lemming's sprite size
	 * \return A vector with the sprite size (x for width and y for height)
	 */
	Vec2 getSpriteSize() const { return m_lemmingSpriteSize; }


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

	LemmingState m_currentState{};
	LemmingActionState m_actionState{};

	int m_currentAcceleration{};

	Vec2 m_lemmingSpriteSize;

	Sprite* m_pIdleSpriteFrame{};
	Vector<SpriteFrame*> m_pFallingSpriteFrames;
	Vector<SpriteFrame*> m_pWalkingSpriteFrames;
	Vector<SpriteFrame*> m_pMiningSpriteFrames;

	void CreateSpriteFrames(Lemming*, const char* filePath);

	Vector<SpriteFrame*> CreateSpriteFramesFromImage(Vec2 startingPoint, int nbFrames, const char* filePath);

	void Move() const;

	void UpdateMovementStateAndAnimation();

	void RunWithAnimation(const Vector<SpriteFrame*>& frames, bool isFlipped);

	void DoAction();

	void Block();

	void ReturnToDefaultState();
};
