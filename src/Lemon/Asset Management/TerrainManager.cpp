#include "TerrainManager.h"
#include "Terrain/Terrain.h"
#include "Asset Management/TextureManager.h"

TerrainManager* TerrainManager::m_pInstance;

TerrainManager::TerrainManager()
{
	privLoad("LEMON_EDITOR_GRID", "HM257x257_flat.tga", "LEMON_DEFAULT_TILE", 8192, 0, 0, 100, 100);
}

TerrainManager::~TerrainManager()
{
	for (std::pair<std::string, Terrain*> item : m_loadedTerrains)
	{
		delete item.second;
	}
	m_loadedTerrains.clear();
}

TerrainManager& TerrainManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new TerrainManager;
	}
	return *m_pInstance;
}

void TerrainManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void TerrainManager::privLoad(std::string id, std::string path, std::string texID, float sideLen, float maxHeight, float yTrans, int repeatU, int repeatV)
{
	if (m_loadedTerrains.find(id) != m_loadedTerrains.end()) // id is not unique
	{
		Trace::out("LOAD ERROR: Terrain ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	path = "Heightmaps/" + path;
	Terrain* pTerrain = new Terrain(path.c_str(), sideLen, maxHeight, yTrans, repeatU, repeatV, TextureManager::Get(texID));
	m_loadedTerrains.insert(std::pair<std::string, Terrain*>(id, pTerrain));
}

Terrain* TerrainManager::privGet(std::string id)
{
	if (m_loadedTerrains.find(id) == m_loadedTerrains.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Terrain ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedTerrains.find(id)->second;
}

std::map<std::string, Terrain*>::iterator TerrainManager::GetIt(std::string id)
{
	TerrainManager& instance = Instance();

	return instance.m_loadedTerrains.find(id);
}

std::map<std::string, Terrain*>::iterator TerrainManager::GetNext(std::map<std::string, Terrain*>::iterator in)
{
	TerrainManager& instance = Instance();

	auto it = instance.m_loadedTerrains.end();
	if (in == --instance.m_loadedTerrains.end()) return in;
	else return ++in;
}

std::map<std::string, Terrain*>::iterator TerrainManager::GetPrev(std::map<std::string, Terrain*>::iterator in)
{
	TerrainManager& instance = Instance();

	if (in == instance.m_loadedTerrains.begin()) return in;
	else return --in;
}
