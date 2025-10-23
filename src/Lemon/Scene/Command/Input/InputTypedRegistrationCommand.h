#ifndef _InputTypedRegistrationCommand
#define _InputTypedRegistrationCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"
#include "GameObject/InputTypes.h"

class Inputable;

class InputTypedRegistrationCommand : public Command
{
public:
	InputTypedRegistrationCommand(Inputable* pInputable);
	InputTypedRegistrationCommand() = delete;
	InputTypedRegistrationCommand(const InputTypedRegistrationCommand&) = delete;
	InputTypedRegistrationCommand& operator = (const InputTypedRegistrationCommand&) = delete;
	~InputTypedRegistrationCommand() = default;

private:
	Inputable*				m_pInputable;

public:
	void					Execute() override;
};

#endif _InputTypedRegistrationCommand