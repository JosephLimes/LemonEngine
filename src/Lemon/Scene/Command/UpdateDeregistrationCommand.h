#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "Command.h"

class Updatable;

class UpdateDeregistrationCommand : public Command
{
public:
	UpdateDeregistrationCommand(Updatable* pUpdatable);
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator = (const UpdateDeregistrationCommand&) = delete;
	~UpdateDeregistrationCommand() = default;

private:
	Updatable*				m_pUpdatable;

public:
	void					Execute() override;
};

#endif _UpdateDeregistrationCommand