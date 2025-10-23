#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputDeregistrationCommand : public Command
{
public:
	InputDeregistrationCommand(Inputable* pInputable, AZUL_KEY key, KeyEvent event);
	InputDeregistrationCommand() = delete;
	InputDeregistrationCommand(const InputDeregistrationCommand&) = delete;
	InputDeregistrationCommand& operator = (const InputDeregistrationCommand&) = delete;
	~InputDeregistrationCommand() = default;

private:
	Inputable*				m_pInputable;
	AZUL_KEY				m_key;
	KeyEvent				m_event;

public:
	void					Execute() override;
};

#endif _InputDeregistrationCommand