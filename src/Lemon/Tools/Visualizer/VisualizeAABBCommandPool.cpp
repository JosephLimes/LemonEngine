#include "VisualizeAABBCommandPool.h"
#include "VisualizeAABBCommand.h"

VisualizeAABBCommandPool::~VisualizeAABBCommandPool()
{
	while (!m_commands.empty())
	{
		delete m_commands.top();
		m_commands.pop();
	}
}

VisualizeAABBCommand* VisualizeAABBCommandPool::GetCommand(Matrix& world, const Vect& color)
{
	VisualizeAABBCommand* pCmd;

	if (m_commands.empty())
	{
		pCmd = new VisualizeAABBCommand(world, color);
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
void VisualizeAABBCommandPool::RecycleCommand(VisualizeAABBCommand* pCmd)
{
	m_commands.push(pCmd);
}
