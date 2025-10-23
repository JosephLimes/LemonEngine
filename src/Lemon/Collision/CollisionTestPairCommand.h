#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "../Scene/Command/Command.h"

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTestPairCommand : public Command
{
public:
	CollisionTestPairCommand(CollidableGroup* pGroup1, CollidableGroup* pGroup2, CollisionDispatchBase* pDispatch);

	CollisionTestPairCommand() = default;
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand operator = (const CollisionTestPairCommand&) = delete;
	~CollisionTestPairCommand();

private:
	CollisionDispatchBase*	m_pDispatch;
	CollidableGroup*		m_pGroup1;
	CollidableGroup*		m_pGroup2;

public:
	void					Execute() override;
};

#endif _CollisionTestPairCommand