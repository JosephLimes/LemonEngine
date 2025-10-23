#ifndef _TypedInput
#define _TypedInput

#include "InputStrategy.h"

class TypedInput : public InputStrategy
{
public:
	TypedInput(KeyboardInputManager* pManager);
	TypedInput() = delete;
	TypedInput(const TypedInput&) = delete;
	TypedInput& operator = (const TypedInput&) = delete;
	~TypedInput() = default;

	virtual void Process();
	virtual void QueueInput(int key);
};

#endif _TypedInput