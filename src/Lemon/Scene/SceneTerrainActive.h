#ifndef _SceneTerrainActive
#define _SceneTerrainActive

#include "SceneTerrain.h"

class SceneTerrainActive : public SceneTerrain
{
public:
	SceneTerrainActive(Terrain* pTerrain);
	SceneTerrainActive() = default;
	SceneTerrainActive(const SceneTerrainActive&) = delete;
	SceneTerrainActive& operator = (const SceneTerrainActive&) = delete;
	~SceneTerrainActive() = default;

	virtual void				Draw() override;
	virtual void				SetTerrain(Terrain* pTerrain) override;
	virtual Terrain*			GetTerrain() override;
	virtual Terrain::CellIndex	CellAt(const Vect& pos) const override;
};

#endif _SceneTerrainActive