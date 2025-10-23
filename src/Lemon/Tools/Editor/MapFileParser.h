#ifndef _MapFileParser
#define _MapFileParser

#include <vector>

#include "MapFile.h"

class LevelObject;
class EditorAdmin;

class MapFileParser
{
	friend class MapFileParserAttorney;

private:
	MapFileParser() = default;
	MapFileParser(const MapFileParser&) = delete;
	MapFileParser operator = (const MapFileParser&) = delete;
	~MapFileParser() = default;

	static MapFileParser*	m_pInstance;

	static const int		m_bufferSize = 4096;

	static MapFileParser&	Instance();
	static void				Terminate();

public:
	static void				WriteMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, std::string terrainID) { Instance().privWriteMapFile(filename, lvlObjs, flaglist, terrainID); };
	static void				ReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, EditorAdmin* pAdmin) { Instance().privReadMapFile(filename, lvlObjs, flaglist, pAdmin); };
	static void				ReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs) { Instance().privReadMapFile(filename, lvlObjs); };
	static void				ParseFlags(LevelObject* pObj, LevelObjectFlags flags) { Instance().privParseFlags(pObj, flags); }

private:
	static void				privWriteMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, std::string terrainID);
	static void				privReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, EditorAdmin* pAdmin);
	static void				privReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs);
	static void				privParseFlags(LevelObject* pObj, LevelObjectFlags flags);
};

#endif _MapFileParser