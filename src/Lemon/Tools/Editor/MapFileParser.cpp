#include "MapFileParser.h"

#include <fstream>

#include "LevelObject.h"
#include "LevelObjectAttorney.h"
#include "LevelObjectManager.h"
#include "MapFile.h"
#include "Scene/SceneAttorney.h"
#include "EditorAdmin.h"

MapFileParser* MapFileParser::m_pInstance;

MapFileParser& MapFileParser::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new MapFileParser;
	}
	return *m_pInstance;
}

void MapFileParser::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void MapFileParser::privWriteMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, std::string terrainID)
{
	// open file, write binary
	std::ofstream file(filename, std::ios::binary);

	// set up our buffer
	unsigned int serialSize = sizeof(LevelObjectHeader) + sizeof(Matrix);
	unsigned int bufferPos = sizeof(LemonMapFileHeader); // we are going to store the objects before writing the header
	unsigned int size = 0;
	char buffer[m_bufferSize];
	memset(buffer, 'x', m_bufferSize); // set buffer to single char for debugging

	// write terrain ID and length to buffer before level objects
	unsigned int terrainIDlen = terrainID.length();
	memcpy(buffer + bufferPos, &terrainIDlen, sizeof(unsigned int));
	bufferPos += sizeof(unsigned int);
	terrainID.copy(buffer + bufferPos, terrainID.length());
	bufferPos += terrainID.length();

	// serialize each level object in our buffer
	auto it = flaglist.begin(); // iterate through flag list simultaneously
	for (LevelObject* lvlObj : lvlObjs)
	{
		lvlObj->Serialize(buffer + bufferPos, *it);
		bufferPos += serialSize;
		size++;
		it++;
	}

	// create file header
	LemonMapFileHeader fileheader;
	fileheader.objectCount = size;

	// add header to the start of our buffer
	memcpy(buffer, &fileheader, sizeof(LemonMapFileHeader));

	// write buffer to file and close
	file.write(buffer, bufferPos);
	file.close();
}

// Load into editor
void MapFileParser::privReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs, std::vector<LevelObjectFlags>& flaglist, EditorAdmin* pAdmin)
{
	// open our file for reading binary
	std::ifstream file(filename, std::ios::binary);

	char buffer[m_bufferSize];

	// load to our buffer and close file
	file.read(buffer, m_bufferSize);
	file.close();

	// grab file header
	LemonMapFileHeader fileheader;
	memcpy(&fileheader, buffer, sizeof(LemonMapFileHeader));

	assert(fileheader.version == LEMON_MAP_FILE_VERSION); // no backwards compatibility right now

	unsigned int bufferPos = sizeof(LemonMapFileHeader); // start reading after header

	// set terrain if specified in the file
	unsigned int terrainIDlen;
	memcpy(&terrainIDlen, buffer + bufferPos, sizeof(unsigned int));
	bufferPos += sizeof(unsigned int);
	if (terrainIDlen > 0) // map contains a specified terrain
	{
		std::string terrainID(buffer + bufferPos, terrainIDlen);
		terrainID;
		//SceneAttorney::SetTerrain(terrainID);
		pAdmin->UpdateTerrain(terrainID);
	}
	bufferPos += terrainIDlen;

	// populate our level with serialized level objects
	unsigned int serialSize = sizeof(LevelObjectHeader) + sizeof(Matrix);
	Matrix world;
	for (int i = 0; i < fileheader.objectCount; i++)
	{
		// get object header
		LevelObjectHeader header;
		memcpy(&header, buffer + bufferPos, sizeof(LevelObjectHeader));

		// create object of correct type
		LevelObject* pLO = LevelObjectManager::Get(header.ID);

		// copy world matrix data and set object's world with it
		memcpy(&world, buffer + bufferPos + sizeof(LevelObjectHeader), sizeof(Matrix));

		LevelObjectAttorney::SetLevelWorld(pLO, world);
		pLO->LevelInitialize();
		//privParseFlags(pLO, header.flags);
		flaglist.push_back(header.flags);

		lvlObjs.push_back(pLO);

		bufferPos += serialSize;
	}
}

// Load into scene
void MapFileParser::privReadMapFile(std::string filename, std::vector<LevelObject*>& lvlObjs)
{
	// open our file for reading binary
	std::ifstream file(filename, std::ios::binary);

	char buffer[m_bufferSize];

	// load to our buffer and close file
	file.read(buffer, m_bufferSize);
	file.close();

	// grab file header
	LemonMapFileHeader fileheader;
	memcpy(&fileheader, buffer, sizeof(LemonMapFileHeader));

	assert(fileheader.version == LEMON_MAP_FILE_VERSION); // no backwards compatibility right now

	unsigned int bufferPos = sizeof(LemonMapFileHeader); // start reading after header

	// set terrain if specified in the file
	unsigned int terrainIDlen;
	memcpy(&terrainIDlen, buffer + bufferPos, sizeof(unsigned int));
	bufferPos += sizeof(unsigned int);
	if (terrainIDlen > 0) // map contains a specified terrain
	{
		std::string terrainID(buffer + bufferPos, terrainIDlen);
		terrainID;
		SceneAttorney::SetTerrain(terrainID);
	}
	bufferPos += terrainIDlen;

	// populate our level with serialized level objects
	unsigned int serialSize = sizeof(LevelObjectHeader) + sizeof(Matrix);
	Matrix world;
	for (int i = 0; i < fileheader.objectCount; i++)
	{
		// get object header
		LevelObjectHeader header;
		memcpy(&header, buffer + bufferPos, sizeof(LevelObjectHeader));

		// create object of correct type
		LevelObject* pLO = LevelObjectManager::Get(header.ID);

		// copy world matrix data and set object's world with it
		memcpy(&world, buffer + bufferPos + sizeof(LevelObjectHeader), sizeof(Matrix));

		LevelObjectAttorney::SetLevelWorld(pLO, world);
		pLO->LevelInitialize();
		privParseFlags(pLO, header.flags);

		lvlObjs.push_back(pLO);

		bufferPos += serialSize;
	}
}

void MapFileParser::privParseFlags(LevelObject* pObj, LevelObjectFlags flags)
{
	if (flags.Check(LevelObjectFlagValue::UPDATABLE))
	{
		pObj->Updatable::SubmitRegistration();
	}

	if (flags.Check(LevelObjectFlagValue::DRAWABLE))
	{
		pObj->Drawable::SubmitRegistration();
	}

	if (flags.Check(LevelObjectFlagValue::COLLIDABLE))
	{
		pObj->Collidable::SubmitRegistration();
	}
}
