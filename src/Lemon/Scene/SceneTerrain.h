#ifndef _SceneTerrain
#define _SceneTerrain

#include "Terrain/Terrain.h"

class SceneTerrain
{
public:
	SceneTerrain() = default;
	SceneTerrain(const SceneTerrain&) = delete;
	SceneTerrain& operator = (const SceneTerrain&) = delete;
	virtual ~SceneTerrain() = default;

protected:
	Terrain*					m_pTerrain;

public:
	virtual void				Draw() = 0;
	virtual void				SetTerrain(Terrain* pTerrain) = 0;
	virtual Terrain*			GetTerrain() = 0;
	virtual Terrain::CellIndex	CellAt(const Vect& pos) const = 0;
};

#endif _SceneTerrain