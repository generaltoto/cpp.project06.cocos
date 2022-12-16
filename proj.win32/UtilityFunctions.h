#pragma once

#include "cmath"
#include "cfloat"
#include "cocos2d.h"

/**
 * \brief Checks if a float is almost null
 * \param f The float number to check
 * \return True if float is null
 */
bool isFloatNull(float f);

/**
 * \brief Checks if a point is in a given rectangle 
 * \param rectCoordinates The rectangle's coordinates
 * \param rectSize The rectangle size
 * \param pointPosition The point's coordinates
 * \return True if the point is in the rectangle
 */
bool isInRectCoordinates(
	const cocos2d::Vec2& rectCoordinates,
	const cocos2d::Vec2& rectSize,
	const cocos2d::Vec2& pointPosition
);