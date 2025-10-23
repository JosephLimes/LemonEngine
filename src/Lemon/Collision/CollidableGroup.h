#ifndef _CollidableGroup
#define _CollidableGroup

#include "AzulCore.h"
#include "../Scene/CollisionManager.h"

class CollisionVolumeAABB;

class CollidableGroup
{
public:
	using CollidableCollection = std::list<Collidable*>;

	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator = (const CollidableGroup&) = delete;
	~CollidableGroup();

private:
	CollidableCollection		m_collidableCollection;
	CollisionVolumeAABB*		m_pAABB; // encompassing all members of group

public:
	const CollidableCollection& GetColliderCollection();
	const CollisionVolumeAABB&	GetAABB();
	void						SetAABB(Vect min, Vect max);
	void						Register(Collidable* pObj, CollisionManager::ListRef& ref);
	void						Deregister(const CollisionManager::ListRef& ref);
	
};

#endif _CollidableGroup