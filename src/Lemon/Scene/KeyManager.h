#ifndef _KeyManager
#define _KeyManager

#include "AzulCore.h"
#include "GameObject/InputTypes.h"

#include <list>

class Inputable;

class KeyManager
{
public:
	// figure out where this should live
	// Type for Inputables to store a reference in KeyManager's lists
	using ListRef = std::list<Inputable*>::iterator;

	KeyManager(AZUL_KEY key);
	KeyManager() = delete;
	KeyManager(const KeyManager&) = delete;
	KeyManager& operator = (const KeyManager&) = delete;
	~KeyManager() = default;

private:
	AZUL_KEY				m_key;
	bool					m_previouslyPressed; // previous frame state     
	std::list<Inputable*>	m_registeredPress;
	std::list<Inputable*>	m_registeredRelease;

public:
	void					ProcessKeyEvents();

	void					Register(Inputable* pObj, KeyEvent event, ListRef& ref);
	void					Deregister(KeyEvent event, const ListRef& ref);
};

#endif _KeyManager