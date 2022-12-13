#pragma once

#include "cocos2d.h"

class Lemming
{
public:
	cocos2d::Sprite* sprite;

	const float lemmingVelocity = 30;

	float lemmingAcceleration = 1;
};

