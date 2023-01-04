#include "UtilityFunctions.h"

bool isFloatNull(float f)
{
	return ((static_cast<int>(f) * 100) * 0.01 == 0);
}

bool isInRectCoordinates(
	const cocos2d::Vec2& rectCoordinates,
	const cocos2d::Vec2& rectSize,
	const cocos2d::Vec2& pointPosition
)
{
	if (
		pointPosition.x >= rectCoordinates.x &&
		pointPosition.x <= rectCoordinates.x + rectSize.x &&
		pointPosition.y <= rectCoordinates.y &&
		pointPosition.y >= rectCoordinates.y - rectSize.y
		) return true;
	return false;
}

