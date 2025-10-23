#ifndef _TerrainManager
#define _TerrainManager

#include <map>

class Terrain;

//todo doc

class TerrainManager
{
	friend class TerrainManagerAttorney;

private:
	TerrainManager();
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator = (const TerrainManager&) = delete;
	~TerrainManager();

	static TerrainManager*			m_pInstance;
	std::map<std::string, Terrain*>	m_loadedTerrains;

	static TerrainManager&			Instance();

public:
	static void						Load(std::string id, std::string path, std::string texID, float sideLen, float maxHeight, float yTrans, int repeatU, int repeatV) { Instance().privLoad(id, path, texID, sideLen, maxHeight, yTrans, repeatU, repeatV); }
	static Terrain*					Get(std::string id) { return Instance().privGet(id); }

private:
	static void						Terminate();

	void							privLoad(std::string id, std::string path, std::string texID, float sideLen, float maxHeight, float yTrans, int repeatU, int repeatV);
	Terrain*						privGet(std::string id);

	// used by the editor to cycle terrains
	static std::map<std::string, Terrain*>::iterator GetIt(std::string id);
	static std::map<std::string, Terrain*>::iterator GetNext(std::map<std::string, Terrain*>::iterator in);
	static std::map<std::string, Terrain*>::iterator GetPrev(std::map<std::string, Terrain*>::iterator in);
};

#endif _TerrainManager