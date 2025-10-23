#ifndef _StandardInput
#define _StandardInput

#include "InputStrategy.h"

class StandardInput : public InputStrategy
{
public:
	StandardInput(KeyboardInputManager* pManager);
	StandardInput() = delete;
	StandardInput(const StandardInput&) = delete;
	StandardInput& operator = (const StandardInput&) = delete;
	~StandardInput() = default;

	virtual void Process();
	virtual void QueueInput(int key);
};

#endif _StandardInput