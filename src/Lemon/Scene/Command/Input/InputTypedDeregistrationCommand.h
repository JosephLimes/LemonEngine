#ifndef _InputTypedDeregistrationCommand
#define _InputTypedDeregistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputTypedDeregistrationCommand : public Command
{
public:
	InputTypedDeregistrationCommand(Inputable* pInputable);
	InputTypedDeregistrationCommand() = delete;
	InputTypedDeregistrationCommand(const InputTypedDeregistrationCommand&) = delete;
	InputTypedDeregistrationCommand& operator = (const InputTypedDeregistrationCommand&) = delete;
	~InputTypedDeregistrationCommand() = default;

private:
	Inputable*				m_pInputable;

public:
	void					Execute() override;
};

#endif _InputTypedDeregistrationCommand