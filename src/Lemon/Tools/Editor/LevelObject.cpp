#include "LevelObject.h"
#include "MapFileParser.h"
#include "MapFile.h"

void LevelObject::Serialize(char* const buffer, LevelObjectFlags flags)
{
	LevelObjectHeader header;
	header.ID = GetTypeID();
	header.flags.Set(flags);
	memcpy(buffer, &header, sizeof(LevelObjectHeader));
	memcpy(buffer + sizeof(LevelObjectHeader), &m_world, sizeof(Matrix));
}

void LevelObject::SetLevelWorldMat(Matrix& world)
{
	m_world = world;
}

Matrix& LevelObject::GetLevelWorldMat()
{
	return m_world;
}
