#include "InputTypedRegistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputTypedRegistrationCommand::InputTypedRegistrationCommand(Inputable* pInputable)
	: m_pInputable(pInputable)
{}

void InputTypedRegistrationCommand::Execute()
{
	InputableAttorney::Registration::RegisterTyped(m_pInputable);
}
