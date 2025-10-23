#ifndef _VisualizePointCommandPool
#define _VisualizePointCommandPool

#include <stack>

class Vect;
class VisualizePointCommand;

class VisualizePointCommandPool
{
public:
	VisualizePointCommandPool() = default;
	VisualizePointCommandPool(const VisualizePointCommandPool&) = default;
	VisualizePointCommandPool operator = (const VisualizePointCommandPool&) = delete;
	~VisualizePointCommandPool();

private:
	std::stack<VisualizePointCommand*>	m_commands;

public:
	VisualizePointCommand*				GetCommand(const Vect& pos, const Vect& color);
	void								RecycleCommand(VisualizePointCommand* pCmd);
};

#endif _VisualizePointCommandPool