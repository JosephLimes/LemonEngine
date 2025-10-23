#include "InputDeregistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* pInputable, AZUL_KEY key, KeyEvent event)
	: m_pInputable(pInputable), m_key(key), m_event(event) {}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::Deregister(m_pInputable, m_key, m_event);
}
