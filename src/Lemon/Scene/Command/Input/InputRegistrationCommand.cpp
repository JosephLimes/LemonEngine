#include "InputRegistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* pInputable, AZUL_KEY key, KeyEvent event)
	: m_pInputable(pInputable), m_key(key), m_event(event) {}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::Register(m_pInputable, m_key, m_event);
}
