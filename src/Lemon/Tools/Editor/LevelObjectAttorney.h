#ifndef _LevelObjectAttorney
#define _LevelObjectAttorney

#include "LevelObject.h"

class LevelObjectAttorney
{
public:
	friend class MapFileParser;
	friend class EditorAdmin;

	LevelObjectAttorney() = delete;
	LevelObjectAttorney(const LevelObjectAttorney&) = delete;
	LevelObjectAttorney& operator = (const LevelObjectAttorney&) = delete;
	~LevelObjectAttorney() = delete;

private:
	// passthrough for parser and marker
	static void			SetLevelWorld(LevelObject* pObj, Matrix& world) { pObj->SetLevelWorldMat(world); }
	static Matrix&		GetLevelWorld(LevelObject* pObj) { return pObj->GetLevelWorldMat(); }
};

#endif _LevelObjectAttorney