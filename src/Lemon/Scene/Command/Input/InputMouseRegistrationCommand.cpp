#include "InputMouseRegistrationCommand.h"
#include "GameObject/InputableAttorney.h"

InputMouseRegistrationCommand::InputMouseRegistrationCommand(Inputable* pInputable, AZUL_MOUSE button, ButtonEvent event)
	: m_pInputable(pInputable), m_button(button), m_event(event) 
{}

void InputMouseRegistrationCommand::Execute()
{
	InputableAttorney::Registration::Register(m_pInputable, m_button, m_event);
}
