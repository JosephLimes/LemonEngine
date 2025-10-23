#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "../Scene/Command/Command.h"

class Terrain;
class CollidableGroup;

class CollisionTestTerrainCommand : public Command
{
public:
	CollisionTestTerrainCommand(Terrain* pTerrain, CollidableGroup* pGroup);

	CollisionTestTerrainCommand() = default;
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand operator = (const CollisionTestTerrainCommand&) = delete;
	~CollisionTestTerrainCommand() = default;

private:
	Terrain*				m_pTerrain;
	CollidableGroup*		m_pGroup;

public:
	void					Execute() override;
};

#endif _CollisionTestTerrainCommand