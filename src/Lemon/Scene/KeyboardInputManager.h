#ifndef _KeyboardInputManager
#define _KeyboardInputManager

#include <list>
#include <map>

#include "AzulCore.h"

#include "GameObject/InputTypes.h"

class Inputable;
class KeyManager;
class InputStrategy;
class StandardInput;
class TypedInput;

class KeyboardInputManager
{
public:
	// Type for Inputables to store a reference in KeyManager's lists
	using ListRef = std::list<Inputable*>::iterator;

	KeyboardInputManager();
	KeyboardInputManager(const KeyboardInputManager&) = delete;
	KeyboardInputManager& operator = (const KeyboardInputManager&) = delete;
	~KeyboardInputManager();

private:
	std::map<AZUL_KEY, KeyManager*>		m_registeredKeys;
	
	// input strategy objects
	StandardInput*						m_standardInput;
	TypedInput*							m_typedInput;
	InputStrategy*						m_inputStrategy;

	// typed input
	std::list<Inputable*>				m_registeredTyped;
	std::list<char>						m_queuedChars;

public:
	void								Register(Inputable* pObj, AZUL_KEY key, KeyEvent event, ListRef& ref);
	void								Deregister(AZUL_KEY key, KeyEvent event, const ListRef& ref);
	void								RegisterTyped(Inputable* pObj, ListRef& ref);
	void								DeregisterTyped(ListRef& ref);
	void								ProcessElements();
	void								ProcessStandardInput();
	void								ProcessTypedInput();
	void								QueueInput(int key); // calls strategy
	void								QueueInput(char key); // called by strategy
	void								SetInputMode(InputMode mode);
};

#endif _KeyboardInputManager