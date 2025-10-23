#include "StandardInput.h"
#include "KeyboardInputManager.h"

StandardInput::StandardInput(KeyboardInputManager* pManager)
	: InputStrategy(pManager)
{}

void StandardInput::Process()
{
	m_manager->ProcessStandardInput();
}

void StandardInput::QueueInput(int key)
{
	key;
	// empty, we aren't typing in standard mode
}
