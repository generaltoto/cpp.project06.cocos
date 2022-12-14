#include "UtilityFunctions.h"

bool isFloatNull(float f)
{
	return ((static_cast<int>(f) * 100) * 0.01 == 0);
}
