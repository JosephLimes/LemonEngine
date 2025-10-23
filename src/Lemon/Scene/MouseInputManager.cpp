#include "MouseInputManager.h"
#include "ButtonManager.h"
#include "GameObject/InputableAttorney.h"

MouseInputManager::~MouseInputManager()
{
	std::map<AZUL_MOUSE, ButtonManager*>::iterator it;
	for (it = m_registeredButtons.begin(); it != m_registeredButtons.end(); it++)
	{
		delete it->second;
	}
}

void MouseInputManager::Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event, ListRef& ref)
{
	std::map<AZUL_MOUSE, ButtonManager*>::iterator it = m_registeredButtons.find(button);

	if (it == m_registeredButtons.end()) // key has never been registered, create new single key manager
	{
		it = m_registeredButtons.insert(m_registeredButtons.end(), std::pair<AZUL_MOUSE, ButtonManager*>(button, new ButtonManager(button)));
	}

	it->second->Register(pObj, event, ref);
}

void MouseInputManager::Deregister(AZUL_MOUSE button, ButtonEvent event, const ListRef& ref)
{
	std::map<AZUL_MOUSE, ButtonManager*>::iterator it = m_registeredButtons.find(button);

	assert(it != m_registeredButtons.end()); // key has never been registered, something is wrong

	it->second->Deregister(event, ref);
}

void MouseInputManager::ProcessElements()
{
	std::map<AZUL_MOUSE, ButtonManager*>::iterator it;
	for (it = m_registeredButtons.begin(); it != m_registeredButtons.end(); it++)
	{
		it->second->ProcessButtonEvents();
	}
}