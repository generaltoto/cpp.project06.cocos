#include "UtilityFunctions.h"

bool isFloatNull(float f)
{
	if (abs(f) <= FLT_EPSILON) return true;
	return false;
}
