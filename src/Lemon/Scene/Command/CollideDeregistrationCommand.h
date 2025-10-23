#ifndef _CollideDeregistrationCommand
#define _CollideDeregistrationCommand

#include "Command.h"

class Collidable;

class CollideDeregistrationCommand : public Command
{
public:
	CollideDeregistrationCommand(Collidable* pCollidable);
	CollideDeregistrationCommand() = delete;
	CollideDeregistrationCommand(const CollideDeregistrationCommand&) = delete;
	CollideDeregistrationCommand& operator = (const CollideDeregistrationCommand&) = delete;
	~CollideDeregistrationCommand() = default;

private:
	Collidable*				m_pCollidable;

public:
	void					Execute() override;
};

#endif _CollideDeregistrationCommand