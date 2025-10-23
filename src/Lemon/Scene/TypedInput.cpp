#include "TypedInput.h"
#include "KeyboardInputManager.h"

TypedInput::TypedInput(KeyboardInputManager* pManager)
	: InputStrategy(pManager)
{}

void TypedInput::Process()
{
	m_manager->ProcessTypedInput();
}

void TypedInput::QueueInput(int key)
{
	char c = char(key);
	m_manager->QueueInput(c);
}
