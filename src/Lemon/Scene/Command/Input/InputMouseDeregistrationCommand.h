#ifndef _InputMouseDeregistrationCommand
#define _InputMouseDeregistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputMouseDeregistrationCommand : public Command
{
public:
	InputMouseDeregistrationCommand(Inputable* pInputable, AZUL_MOUSE button, ButtonEvent event);
	InputMouseDeregistrationCommand() = delete;
	InputMouseDeregistrationCommand(const InputMouseDeregistrationCommand&) = delete;
	InputMouseDeregistrationCommand& operator = (const InputMouseDeregistrationCommand&) = delete;
	~InputMouseDeregistrationCommand() = default;

private:
	Inputable*				m_pInputable;
	AZUL_MOUSE				m_button;
	ButtonEvent				m_event;

public:
	void					Execute() override;
};

#endif _InputMouseDeregistrationCommand