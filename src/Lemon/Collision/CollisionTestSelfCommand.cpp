#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"
#include "GameObject/Collidable.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* pGroup, CollisionDispatchBase* pDispatch)
	: m_pGroup(pGroup), m_pDispatch(pDispatch)
{}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete m_pDispatch;
}

void CollisionTestSelfCommand::Execute()
{
	const CollidableGroup::CollidableCollection& collection = m_pGroup->GetColliderCollection();

	if (collection.size() > 1) // only loop if there are pairs to check
	{
		for (auto it1 = collection.begin(), secondLast = --collection.end(); it1 != secondLast; it1++) // stop at second to last because the last element will have been checked against all
		{
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
			for (auto it2 = std::next(it1, 1); it2 != collection.end(); it2++) // check against every following element, previous have already been checked
			{
				const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();
				
				// Determine if BSpheres intersect before more complicated collision tests
				if (LemonMath::Intersect((*it1)->GetBSphere(), (*it2)->GetBSphere()))
				{
					//Visualizer::ShowBSphere((*it1)->GetBSphere());
					//Visualizer::ShowBSphere((*it2)->GetBSphere());
					// Do proper collision test
					if (LemonMath::Intersect(cv1, cv2))
					{
						//Visualizer::ShowCollisionVolume((*it1)->GetCollisionVolume());
						//Visualizer::ShowCollisionVolume((*it2)->GetCollisionVolume());
						m_pDispatch->ProcessCallbacks(*it1, *it2);
					}
				}
			}
		}
	}

}
