#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Tools/LemonMath.h"
#include "GameObject/Collidable.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Collision/Volumes/CollisionVolumeBSphere.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* pGroup1, CollidableGroup* pGroup2, CollisionDispatchBase* pDispatch)
	: m_pGroup1(pGroup1), m_pGroup2(pGroup2), m_pDispatch(pDispatch)
{}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete m_pDispatch;
}

void CollisionTestPairCommand::Execute()
{
	// Make sure group AABB's collide before continuing
	if (LemonMath::Intersect(m_pGroup1->GetAABB(), m_pGroup2->GetAABB()))
	{
		//Visualizer::ShowAABB(m_pGroup1->GetAABB());
		//Visualizer::ShowAABB(m_pGroup2->GetAABB());

		const CollidableGroup::CollidableCollection& collection1 = m_pGroup1->GetColliderCollection();
		const CollidableGroup::CollidableCollection& collection2 = m_pGroup2->GetColliderCollection();

		for (auto it1 = collection1.begin(); it1 != collection1.end(); it1++)
		{
			const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
			for (auto it2 = collection2.begin(); it2 != collection2.end(); it2++)
			{
				const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();
				const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();

				// Determine if BSpheres intersect before more complicated collision tests
				if (LemonMath::Intersect(bs1, bs2))
				{
					//Visualizer::ShowBSphere(bs1);
					//Visualizer::ShowBSphere(bs2);

					// Determine if actual bounding volumes collide
					if (LemonMath::Intersect(cv1, cv2))
					{
						//Visualizer::ShowCollisionVolume(cv1);
						//Visualizer::ShowCollisionVolume(cv2);

						m_pDispatch->ProcessCallbacks(*it1, *it2);
					}
				}
			}
		}
	}
}
