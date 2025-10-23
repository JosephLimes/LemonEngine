#include "InputMouseDeregistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputMouseDeregistrationCommand::InputMouseDeregistrationCommand(Inputable* pInputable, AZUL_MOUSE button, ButtonEvent event)
	: m_pInputable(pInputable), m_button(button), m_event(event) 
{}

void InputMouseDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::Deregister(m_pInputable, m_button, m_event);
}
