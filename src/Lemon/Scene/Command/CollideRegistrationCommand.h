#ifndef _CollideRegistrationCommand
#define _CollideRegistrationCommand

#include "Command.h"

class Collidable;

class CollideRegistrationCommand : public Command
{
public:
	CollideRegistrationCommand(Collidable* pCollidable);
	CollideRegistrationCommand() = delete;
	CollideRegistrationCommand(const CollideRegistrationCommand&) = delete;
	CollideRegistrationCommand& operator = (const CollideRegistrationCommand&) = delete;
	~CollideRegistrationCommand() = default;

private:
	Collidable*					m_pCollidable;

public:
	void						Execute() override;
};

#endif _CollideRegistrationCommand