#ifndef _MouseInputManager
#define _MouseInputManager

#include <list>
#include <map>

#include "AzulCore.h"

#include "GameObject/InputTypes.h"

class Inputable;
class ButtonManager;

class MouseInputManager
{
public:
	// Type for Inputables to store a reference in KeyManager's lists
	using ListRef = std::list<Inputable*>::iterator;

	MouseInputManager() = default;
	MouseInputManager(const MouseInputManager&) = delete;
	MouseInputManager& operator = (const MouseInputManager&) = delete;
	~MouseInputManager();

private:
	std::map<AZUL_MOUSE, ButtonManager*>m_registeredButtons;

public:
	void								Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event, ListRef& ref);
	void								Deregister(AZUL_MOUSE button, ButtonEvent event, const ListRef& ref);
	void								ProcessElements();
};

#endif _MouseInputManager