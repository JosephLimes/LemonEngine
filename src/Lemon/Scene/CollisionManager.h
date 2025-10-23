#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>
#include "Collision/CollisionTestPairCommand.h"
#include "Collision/CollisionTestSelfCommand.h"
#include "Collision/CollisionTestTerrainCommand.h"
#include "Collision/CollisionDispatch.h"

class Collidable;
class CollidableGroup;
class Terrain;

class CollisionManager
{
public:
	// type for list management
	using ListRef = std::list<Collidable*>::iterator;

	// type for class IDs when processing collisions
	using TypeID = int;
	static const TypeID					ID_UNDEFINED = -1;

	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator = (const CollisionManager&) = delete;
	~CollisionManager();

private:
	using CollidableGroupCollection =	std::vector<CollidableGroup*>;
	CollidableGroupCollection			m_groupCollection;

	using CollisionTestCommands =		std::vector<Command*>;
	std::vector<Command*>				m_collisionTestCommands;

	static TypeID						m_nextTypeID;

public:
	template <typename T>
	TypeID								GetTypeID()
	{
		static TypeID myTypeID = m_nextTypeID++;
		//DebugMsg::out("ID %d assigned.\n", myTypeID);

		SetGroupForTypeID(myTypeID);

		return myTypeID;
	};

	template <typename T>
	void								SetCollisionSelf()
	{
		CollidableGroup* pGroup = m_groupCollection[GetTypeID<T>()];

		CollisionDispatch<T, T>* pDispatch = new CollisionDispatch<T, T>();

		m_collisionTestCommands.push_back(new CollisionTestSelfCommand(pGroup, pDispatch));
	};

	template < typename T1, typename T2>
	void								SetCollisionPair()
	{
		CollidableGroup* pGroup1 = m_groupCollection[GetTypeID<T1>()];
		CollidableGroup* pGroup2 = m_groupCollection[GetTypeID<T2>()];

		CollisionDispatch<T1, T2>* pDispatch = new CollisionDispatch<T1, T2>();

		m_collisionTestCommands.push_back(new CollisionTestPairCommand(pGroup1, pGroup2, pDispatch));
	};

	template <typename T>
	void								SetCollisionTerrain(Terrain* pTerrain)
	{
		CollidableGroup* pGroup = m_groupCollection[GetTypeID<T>()];

		m_collisionTestCommands.push_back(new CollisionTestTerrainCommand(pTerrain, pGroup));
	};

	CollidableGroup*					GetColGroup(TypeID id);

	void								ProcessCollisions();


private:
	void								SetGroupForTypeID(TypeID id);
	void								ProcessGroupAABBs();
};

#endif _CollisionManager