#ifndef _SceneTerrainManager
#define _SceneTerrainManager

class Terrain;
class SceneTerrain;

class SceneTerrainManager
{
public:
	SceneTerrainManager();
	SceneTerrainManager(const SceneTerrainManager&) = delete;
	SceneTerrainManager& operator = (const SceneTerrainManager&) = delete;
	~SceneTerrainManager();
	
private:
	SceneTerrain*		m_pCurrentTerrain;
	SceneTerrain*		m_pActiveTerrain;
	SceneTerrain*		m_pNullTerrain;

public:
	void				Draw();
	void				SetTerrain(Terrain* pTerrain);
	Terrain*			GetTerrain();
};

#endif _SceneTerrainManager