#ifndef _LevelObjectNull
#define _LevelObjectNull

#include "LevelObject.h"

class LevelObjectNull : public LevelObject
{
public:
	LevelObjectNull() { SetCollisionModel(ModelManager::Get("LEMON_DEFAULT_CUBE"), BSPHERE); }; // getCollisionVolume needs to return something
	LevelObjectNull(const LevelObjectNull&) = delete;
	LevelObjectNull& operator = (const LevelObjectNull&) = delete;
	~LevelObjectNull() = default;

	LevelTypeID GetTypeID() override { return 0; }
	virtual void LevelInitialize() override {}
	virtual void LevelTerminate() override {}
};

#endif _LevelObjectNull