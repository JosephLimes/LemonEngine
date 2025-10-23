#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "Command.h"

class Drawable;

class DrawRegistrationCommand : public Command
{
public:
	DrawRegistrationCommand(Drawable* pDrawable);
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator = (const DrawRegistrationCommand&) = delete;
	~DrawRegistrationCommand() = default;

private:
	Drawable*				m_pDrawable;

public:
	void					Execute() override;
};

#endif _DrawRegistrationCommand