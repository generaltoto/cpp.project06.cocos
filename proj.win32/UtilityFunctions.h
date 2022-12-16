#pragma once

#include "cmath"
#include "cfloat"
#include "cocos2d.h"

bool isFloatNull(float f);

bool isInRectCoordinates(
	const cocos2d::Vec2& rectCoordinates,
	const cocos2d::Vec2& rectSize,
	const cocos2d::Vec2& pointPosition
);