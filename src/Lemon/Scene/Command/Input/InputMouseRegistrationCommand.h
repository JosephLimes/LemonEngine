#ifndef _InputMouseRegistrationCommand
#define _InputMouseRegistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputMouseRegistrationCommand : public Command
{
public:
	InputMouseRegistrationCommand(Inputable* pInputable, AZUL_MOUSE button, ButtonEvent event);
	InputMouseRegistrationCommand() = delete;
	InputMouseRegistrationCommand(const InputMouseRegistrationCommand&) = delete;
	InputMouseRegistrationCommand& operator = (const InputMouseRegistrationCommand&) = delete;
	~InputMouseRegistrationCommand() = default;

private:
	Inputable*				m_pInputable;
	AZUL_MOUSE				m_button;
	ButtonEvent				m_event;

public:
	void					Execute() override;
};

#endif _InputMouseRegistrationCommand