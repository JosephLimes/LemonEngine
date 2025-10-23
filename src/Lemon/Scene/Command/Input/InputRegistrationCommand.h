#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputRegistrationCommand : public Command
{
public:
	InputRegistrationCommand(Inputable* pInputable, AZUL_KEY key, KeyEvent event);
	InputRegistrationCommand() = delete;
	InputRegistrationCommand(const InputRegistrationCommand&) = delete;
	InputRegistrationCommand& operator = (const InputRegistrationCommand&) = delete;
	~InputRegistrationCommand() = default;

private:
	Inputable*				m_pInputable;
	AZUL_KEY				m_key;
	KeyEvent				m_event;

public:
	void					Execute() override;
};

#endif _InputRegistrationCommand