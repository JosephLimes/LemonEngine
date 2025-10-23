#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "Command.h"

class Drawable;

class DrawDeregistrationCommand : public Command
{
public:
	DrawDeregistrationCommand(Drawable* pDrawable);
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator = (const DrawDeregistrationCommand&) = delete;
	~DrawDeregistrationCommand() = default;

private:
	Drawable*				m_pDrawable;

public:
	void					Execute() override;
};

#endif _DrawDeregistrationCommand