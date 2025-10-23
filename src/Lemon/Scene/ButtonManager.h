#ifndef _ButtonManager
#define _ButtonManager

#include "AzulCore.h"
#include "GameObject/InputTypes.h"

#include <list>

class Inputable;

class ButtonManager
{
public:
	// figure out where this should live
	// Type for Inputables to store a reference in ButtonManager's lists
	using ListRef = std::list<Inputable*>::iterator;

	ButtonManager(AZUL_MOUSE button);
	ButtonManager() = delete;
	ButtonManager(const ButtonManager&) = delete;
	ButtonManager& operator = (const ButtonManager&) = delete;
	~ButtonManager() = default;

private:
	AZUL_MOUSE				m_button;
	bool					m_previouslyPressed; // previous frame state     
	std::list<Inputable*>	m_registeredPress;
	std::list<Inputable*>	m_registeredRelease;

public:
	void					ProcessButtonEvents();

	void					Register(Inputable* pObj, ButtonEvent event, ListRef& ref);
	void					Deregister(ButtonEvent event, const ListRef& ref);
};

#endif _ButtonManager