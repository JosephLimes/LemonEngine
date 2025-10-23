#include "VisualizePointCommandPool.h"
#include "VisualizePointCommand.h"

VisualizePointCommandPool::~VisualizePointCommandPool()
{
	while (!m_commands.empty())
	{
		delete m_commands.top();
		m_commands.pop();
	}
}

VisualizePointCommand* VisualizePointCommandPool::GetCommand(const Vect& pos, const Vect& color)
{
	VisualizePointCommand* pCmd;

	if (m_commands.empty())
	{
		pCmd = new VisualizePointCommand(pos, color);
	}
	else
	{
		pCmd = m_commands.top();
		m_commands.pop();
		pCmd->Initialize(pos, color);
	}

	return pCmd;
}

// called by the commands themselves
void VisualizePointCommandPool::RecycleCommand(VisualizePointCommand* pCmd)
{
	m_commands.push(pCmd);
}
