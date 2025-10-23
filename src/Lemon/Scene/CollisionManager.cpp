#include "CollisionManager.h"
#include "Collision/CollidableGroup.h"
#include "GameObject/Collidable.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Tools/LemonMath.h"
#include "AzulCore.h"
#include "Tools/Visualizer/Visualizer.h"

CollisionManager::TypeID CollisionManager::m_nextTypeID = 0;

CollisionManager::CollisionManager()
{
	m_groupCollection.push_back(nullptr); // initialize first id as null

	// reinitialize values as null when scene changes and collection gets remade (type ID's persist, so it won't start indexing from 0 when new types are added)
	if (int(m_groupCollection.size()) < m_nextTypeID)
	{
		for (int i = 0; i < m_nextTypeID; i++)
		{
			m_groupCollection.push_back(nullptr);
		}
	}
}

CollisionManager::~CollisionManager()
{
	for (CollidableGroup* pGroup : m_groupCollection)
	{
		delete pGroup;
	}

	for (Command* pCmd : m_collisionTestCommands)
	{
		delete pCmd;
	}
}

CollidableGroup* CollisionManager::GetColGroup(TypeID id)
{
	return m_groupCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	// Update all group AABB's for pruning
	ProcessGroupAABBs();

	// Process actual collisions
	for (Command* pCmd : m_collisionTestCommands)
	{
		pCmd->Execute();
	}
}

void CollisionManager::SetGroupForTypeID(TypeID id)
{

	if (m_groupCollection[id] == nullptr)
	{
		m_groupCollection[id] = new CollidableGroup();
		m_groupCollection.push_back(nullptr); // initialize next id as null
	}
}

void CollisionManager::ProcessGroupAABBs()
{
	for (CollidableGroup* pGroup : m_groupCollection)
	{
		if (pGroup) // end of list will be null, and start/middle can be null after scene change
		{
			const CollidableGroup::CollidableCollection& collection = pGroup->GetColliderCollection();
			if (!collection.empty())
			{
				// initialize groupAABB to first member of group
				CollisionVolumeAABB groupAABB;
				groupAABB.ComputeData(collection.front()->GetBSphere());

				CollisionVolumeAABB	bSphereAABB;

				// grow groupAABB to encompass all group members
				for (Collidable* pCol : collection)
				{
					bSphereAABB.ComputeData(pCol->GetBSphere());
					groupAABB = LemonMath::AABBSum(groupAABB, bSphereAABB);
				}

				// set the group's AABB
				pGroup->SetAABB(groupAABB.GetMin(), groupAABB.GetMax());
			}
		}
	}
}