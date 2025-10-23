#include "SceneTerrainManager.h"
#include "SceneTerrainActive.h"
#include "SceneTerrainNull.h"

SceneTerrainManager::SceneTerrainManager()
{
	m_pActiveTerrain = new SceneTerrainActive();
	m_pNullTerrain = new SceneTerrainNull();

	m_pCurrentTerrain = m_pNullTerrain;
}

SceneTerrainManager::~SceneTerrainManager()
{
	delete m_pActiveTerrain;
	delete m_pNullTerrain;
}

void SceneTerrainManager::Draw()
{
	m_pCurrentTerrain->Draw();
}

void SceneTerrainManager::SetTerrain(Terrain* pTerrain)
{
	m_pActiveTerrain->SetTerrain(pTerrain);
	m_pCurrentTerrain = m_pActiveTerrain;
}

Terrain* SceneTerrainManager::GetTerrain()
{
	return m_pCurrentTerrain->GetTerrain();
}
