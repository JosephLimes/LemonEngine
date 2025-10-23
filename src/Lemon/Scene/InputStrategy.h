#ifndef _InputStrategy
#define _InputStrategy

class KeyboardInputManager;

class InputStrategy
{
public:
	InputStrategy(KeyboardInputManager* pManager) : m_manager(pManager) {};
	InputStrategy() = delete;
	InputStrategy(const InputStrategy&) = delete;
	InputStrategy& operator = (const InputStrategy&) = delete;
	~InputStrategy() = default;

	virtual void			Process() = 0;
	virtual void			QueueInput(int key) = 0;

protected:
	KeyboardInputManager*	m_manager;
};

#endif _InputStrategy