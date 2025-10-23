#include "SceneTerrainActive.h"

SceneTerrainActive::SceneTerrainActive(Terrain* pTerrain)
{
	m_pTerrain = pTerrain;
}

void SceneTerrainActive::Draw()
{
	m_pTerrain->Draw();
}

void SceneTerrainActive::SetTerrain(Terrain* pTerrain)
{
	m_pTerrain = pTerrain;
}

Terrain* SceneTerrainActive::GetTerrain()
{
	return m_pTerrain;
}

Terrain::CellIndex SceneTerrainActive::CellAt(const Vect& pos) const
{
	return m_pTerrain->CellAt(pos);
}
