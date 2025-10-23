#include "ButtonManager.h"
#include "GameObject/InputableAttorney.h"

ButtonManager::ButtonManager(AZUL_MOUSE button)
	: m_button(button), m_previouslyPressed(false) {}

void ButtonManager::ProcessButtonEvents()
{
	bool buttonState = Mouse::GetKeyState(m_button);

	if (buttonState != m_previouslyPressed) // button state has updated, process
	{
		m_previouslyPressed = buttonState;

		if (buttonState == true) // button just pressed
		{
			for (Inputable* pObj : m_registeredPress)
			{
				InputableAttorney::GameLoop::MousePressed(pObj, m_button);
			}
		}
		else // button just released
		{
			for (Inputable* pObj : m_registeredRelease)
			{
				InputableAttorney::GameLoop::MouseReleased(pObj, m_button);
			}
		}
	}
}

void ButtonManager::Register(Inputable* pObj, ButtonEvent event, ListRef& ref)
{
	if (event == ButtonEvent::BUTTON_PRESS)
	{
		ref = m_registeredPress.insert(m_registeredPress.end(), pObj);
	}
	else // event == buttonEvent::button_RELEASE
	{
		ref = m_registeredRelease.insert(m_registeredRelease.end(), pObj);
	}
}

void ButtonManager::Deregister(ButtonEvent event, const ListRef& ref)
{
	if (event == ButtonEvent::BUTTON_PRESS)
	{
		m_registeredPress.erase(ref);
	}
	else // event == buttonEvent::button_RELEASE
	{
		m_registeredRelease.erase(ref);
	}
}
