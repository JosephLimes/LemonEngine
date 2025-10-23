#include "KeyManager.h"
#include "GameObject/InputableAttorney.h"

KeyManager::KeyManager(AZUL_KEY key)
	: m_key(key), m_previouslyPressed(false) {}

void KeyManager::ProcessKeyEvents()
{
	bool keyState = Keyboard::GetKeyState(m_key);

	if (keyState != m_previouslyPressed) // key state has updated, process
	{
		m_previouslyPressed = keyState;

		if (keyState == true) // key just pressed
		{
			for (Inputable* pObj : m_registeredPress)
			{
				InputableAttorney::GameLoop::KeyPressed(pObj, m_key);
			}
		}
		else // key just released
		{
			for (Inputable* pObj : m_registeredRelease)
			{
				InputableAttorney::GameLoop::KeyReleased(pObj, m_key);
			}
		}
	}
}

void KeyManager::Register(Inputable* pObj, KeyEvent event, ListRef& ref)
{
	if (event == KeyEvent::KEY_PRESS)
	{
		ref = m_registeredPress.insert(m_registeredPress.end(), pObj);
	}
	else // event == KeyEvent::KEY_RELEASE
	{
		ref = m_registeredRelease.insert(m_registeredRelease.end(), pObj);
	}
}

void KeyManager::Deregister(KeyEvent event, const ListRef& ref)
{
	if (event == KeyEvent::KEY_PRESS)
	{
		m_registeredPress.erase(ref);
	}
	else // event == KeyEvent::KEY_RELEASE
	{
		m_registeredRelease.erase(ref);
	}
}
