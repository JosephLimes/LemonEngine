#include "KeyboardInputManager.h"
#include "KeyManager.h"
#include "StandardInput.h"
#include "TypedInput.h"
#include "GameObject/InputableAttorney.h"

KeyboardInputManager::KeyboardInputManager()
	: m_standardInput(new StandardInput(this)), m_typedInput(new TypedInput(this)), m_inputStrategy(m_standardInput)
{}

KeyboardInputManager::~KeyboardInputManager()
{
	delete m_standardInput;
	delete m_typedInput;

	std::map<AZUL_KEY, KeyManager*>::iterator it;
	for (it = m_registeredKeys.begin(); it != m_registeredKeys.end(); it++)
	{
		delete it->second;
	}
}

void KeyboardInputManager::Register(Inputable* pObj, AZUL_KEY key, KeyEvent event, ListRef& ref)
{
	
	std::map<AZUL_KEY, KeyManager*>::iterator it = m_registeredKeys.find(key);

	if (it == m_registeredKeys.end()) // key has never been registered, create new single key manager
	{
		it = m_registeredKeys.insert(m_registeredKeys.end(), std::pair<AZUL_KEY, KeyManager*>(key, new KeyManager(key)));
	}

	it->second->Register(pObj, event, ref);
}

void KeyboardInputManager::Deregister(AZUL_KEY key, KeyEvent event, const ListRef& ref)
{
	std::map<AZUL_KEY, KeyManager*>::iterator it = m_registeredKeys.find(key);

	assert(it != m_registeredKeys.end()); // key has never been registered, something is wrong

	it->second->Deregister(event, ref);
}

void KeyboardInputManager::RegisterTyped(Inputable* pObj, ListRef& ref)
{
	ref = m_registeredTyped.insert(m_registeredTyped.end(), pObj);
}

void KeyboardInputManager::DeregisterTyped(ListRef& ref)
{
	m_registeredTyped.erase(ref);
}

void KeyboardInputManager::ProcessElements()
{
	m_inputStrategy->Process();
}

void KeyboardInputManager::ProcessStandardInput()
{
	std::map<AZUL_KEY, KeyManager*>::iterator it;
	for (it = m_registeredKeys.begin(); it != m_registeredKeys.end(); it++)
	{
		it->second->ProcessKeyEvents();
	}
}

void KeyboardInputManager::ProcessTypedInput()
{
	// for each object registered
	for (Inputable* pObj : m_registeredTyped)
	{
		// for each char typed this frame
		for (char c : m_queuedChars)
		{
			InputableAttorney::GameLoop::KeyTyped(pObj, c);
		}
	}

	// clear for next frame
	m_queuedChars.clear();
}

void KeyboardInputManager::QueueInput(int key)
{
	m_inputStrategy->QueueInput(key);
}

void KeyboardInputManager::QueueInput(char key)
{
	m_queuedChars.push_back(key);
}

void KeyboardInputManager::SetInputMode(InputMode mode)
{
	if (mode == InputMode::STANDARD)
	{
		m_inputStrategy = m_standardInput;
	}
	else // mode == InputMode::TYPED
	{
		m_inputStrategy = m_typedInput;
	}
}