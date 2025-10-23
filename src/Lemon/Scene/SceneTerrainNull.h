#ifndef _SceneTerrainNull
#define _SceneTerrainNull

#include "SceneTerrain.h"

class SceneTerrainNull : public SceneTerrain
{
public:
	SceneTerrainNull() = default;
	SceneTerrainNull(const SceneTerrainNull&) = delete;
	SceneTerrainNull& operator = (const SceneTerrainNull&) = delete;
	~SceneTerrainNull() = default;

	virtual void				Draw() override {};
	virtual void				SetTerrain(Terrain* pTerrain) override { pTerrain; };
	virtual Terrain*			GetTerrain() override { return nullptr; }
	virtual Terrain::CellIndex	CellAt(const Vect& pos) const override { pos; return m_ind; };

private:
	const Terrain::CellIndex m_ind = Terrain::CellIndex(-1, -1); // CellAt needs to return a value...
};

#endif _SceneTerrainNull