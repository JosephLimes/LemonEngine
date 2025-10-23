#include "InputTypedDeregistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputTypedDeregistrationCommand::InputTypedDeregistrationCommand(Inputable* pInputable)
	: m_pInputable(pInputable)
{}

void InputTypedDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::DeregisterTyped(m_pInputable);
}
