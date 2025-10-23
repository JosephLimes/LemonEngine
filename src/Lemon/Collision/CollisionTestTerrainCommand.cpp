#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "Terrain/Terrain.h"
#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"
#include "GameObject/Collidable.h"
#include "Terrain/Area.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(Terrain* pTerrain, CollidableGroup* pGroup)
	: m_pTerrain(pTerrain), m_pGroup(pGroup)
{}

void CollisionTestTerrainCommand::Execute()
{
	const CollidableGroup::CollidableCollection& collection = m_pGroup->GetColliderCollection();

	for (auto it = collection.begin(); it != collection.end(); it++)
	{	
		const CollisionVolumeBSphere& bsphere = (*it)->GetBSphere();
		const CollisionVolume& cv = (*it)->GetCollisionVolume();

		Area candidateArea = m_pTerrain->CandidateArea(*it);
		AreaIterator ait = candidateArea.begin();
		while (ait != candidateArea.end())
		{
			// test cell against BSphere first
			if (LemonMath::Intersect(ait.AABB(), bsphere))
			{
				// then proper volume
				if (LemonMath::Intersect(ait.AABB(), cv))
				{
					(*it)->CollisionTerrain();
					break;
				}
			}
			ait++;
		}
	}
}
