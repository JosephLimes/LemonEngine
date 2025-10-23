#include "MapFile.h"

LevelObjectFlagValue operator|(LevelObjectFlagValue lhs, LevelObjectFlagValue rhs)
{
	LevelObjectFlagValue ret = static_cast<LevelObjectFlagValue>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	return ret;
}

LevelObjectFlagValue operator&(LevelObjectFlagValue lhs, LevelObjectFlagValue rhs)
{
	LevelObjectFlagValue ret = static_cast<LevelObjectFlagValue>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	return ret;
}
