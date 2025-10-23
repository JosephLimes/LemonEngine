#include "VisualizeSegmentCommandPool.h"
#include "VisualizeSegmentCommand.h"

VisualizeSegmentCommandPool::~VisualizeSegmentCommandPool()
{
	while (!m_commands.empty())
	{
		delete m_commands.top();
		m_commands.pop();
	}
}

VisualizeSegmentCommand* VisualizeSegmentCommandPool::GetCommand(const Vect& pos1, const Vect& pos2, const Vect& color)
{
	VisualizeSegmentCommand* pCmd;

	if (m_commands.empty())
	{
		pCmd = new VisualizeSegmentCommand(pos1, pos2, color);
	}
	else
	{
		pCmd = m_commands.top();
		m_commands.pop();
		pCmd->Initialize(pos1, pos2, color);
	}

	return pCmd;
}

// called by the commands themselves
void VisualizeSegmentCommandPool::RecycleCommand(VisualizeSegmentCommand* pCmd)
{
	m_commands.push(pCmd);
}
