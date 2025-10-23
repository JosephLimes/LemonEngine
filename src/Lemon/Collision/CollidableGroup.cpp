#include "CollidableGroup.h"
#include "Volumes/CollisionVolumeAABB.h"

CollidableGroup::CollidableGroup()
	: m_pAABB(new CollisionVolumeAABB())
{}

CollidableGroup::~CollidableGroup()
{
	delete m_pAABB;
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return m_collidableCollection;
}

const CollisionVolumeAABB& CollidableGroup::GetAABB()
{
	return *m_pAABB;
}

void CollidableGroup::SetAABB(Vect min, Vect max)
{
	m_pAABB->Set(min,max);
}

void CollidableGroup::Register(Collidable* pObj, CollisionManager::ListRef& ref)
{
	ref = m_collidableCollection.insert(m_collidableCollection.end(), pObj);
}

void CollidableGroup::Deregister(const CollisionManager::ListRef& ref)
{
	m_collidableCollection.erase(ref);
}
