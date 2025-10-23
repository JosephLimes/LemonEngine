#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney

#include "TerrainManager.h"

class TerrainManagerAttorney
{
public:
	friend class Lemon;
	friend class EditorAdmin;

	TerrainManagerAttorney() = delete;
	TerrainManagerAttorney(const TerrainManagerAttorney&) = delete;
	TerrainManagerAttorney& operator = (const TerrainManagerAttorney&) = delete;
	~TerrainManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { TerrainManager::Terminate(); };

	// passthroughs for editor
	static std::map<std::string, Terrain*>::iterator GetIt(std::string id) { return TerrainManager::GetIt(id); };
	static std::map<std::string, Terrain*>::iterator GetNext(std::map<std::string, Terrain*>::iterator in) { return TerrainManager::GetNext(in); };
	static std::map<std::string, Terrain*>::iterator GetPrev(std::map<std::string, Terrain*>::iterator in) { return TerrainManager::GetPrev(in); };
};

#endif _TerrainManagerAttorney