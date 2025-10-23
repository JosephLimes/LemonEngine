#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "Command.h"

class Updatable;

class UpdateRegistrationCommand : public Command
{
public:
	UpdateRegistrationCommand(Updatable* pUpdatable);
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator = (const UpdateRegistrationCommand&) = delete;
	~UpdateRegistrationCommand() = default;

private:
	Updatable*				m_pUpdatable;

public:
	void					Execute() override;
};

#endif _UpdateRegistrationCommand