#include "VisualizeOBBCommandPool.h"
#include "VisualizeOBBCommand.h"

VisualizeOBBCommandPool::~VisualizeOBBCommandPool()
{
	while (!m_commands.empty())
	{
		delete m_commands.top();
		m_commands.pop();
	}
}

VisualizeOBBCommand* VisualizeOBBCommandPool::GetCommand(Matrix& world, const Vect& color)
{
	VisualizeOBBCommand* pCmd;

	if (m_commands.empty())
	{
		pCmd = new VisualizeOBBCommand(world, color);
	}
	else
	{
		pCmd = m_commands.top();
		m_commands.pop();
		pCmd->Initialize(world, color);
	}

	return pCmd;
}

// called by the commands themselves
void VisualizeOBBCommandPool::RecycleCommand(VisualizeOBBCommand* pCmd)
{
	m_commands.push(pCmd);
}
