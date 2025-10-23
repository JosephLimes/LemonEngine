#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "../Scene/Command/Command.h"

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTestSelfCommand : public Command
{
public:
	CollisionTestSelfCommand(CollidableGroup* pGroup, CollisionDispatchBase* pDispatch);

	CollisionTestSelfCommand() = default;
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand operator = (const CollisionTestSelfCommand&) = delete;
	~CollisionTestSelfCommand();

private:
	CollisionDispatchBase*	m_pDispatch;
	CollidableGroup*		m_pGroup;

public:
	void					Execute() override;
};

#endif _CollisionTestSelfCommand