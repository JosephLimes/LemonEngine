#ifndef _VisualizeSegmentCommandPool
#define _VisualizeSegmentCommandPool

#include <stack>

class Vect;
class VisualizeSegmentCommand;

class VisualizeSegmentCommandPool
{
public:
	VisualizeSegmentCommandPool() = default;
	VisualizeSegmentCommandPool(const VisualizeSegmentCommandPool&) = default;
	VisualizeSegmentCommandPool operator = (const VisualizeSegmentCommandPool&) = delete;
	~VisualizeSegmentCommandPool();

private:
	std::stack<VisualizeSegmentCommand*>	m_commands;

public:
	VisualizeSegmentCommand*				GetCommand(const Vect& pos1, const Vect& pos2, const Vect& color);
	void									RecycleCommand(VisualizeSegmentCommand* pCmd);
};

#endif _VisualizeSegmentCommandPool