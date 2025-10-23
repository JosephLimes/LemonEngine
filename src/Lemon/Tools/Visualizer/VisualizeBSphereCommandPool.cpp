#include "VisualizeBSphereCommandPool.h"
#include "VisualizeBSphereCommand.h"

VisualizeBSphereCommandPool::~VisualizeBSphereCommandPool()
{
	while (!m_commands.empty())
	{
		delete m_commands.top();
		m_commands.pop();
	}
}

VisualizeBSphereCommand* VisualizeBSphereCommandPool::GetCommand(Matrix& world, const Vect& color)
{
	VisualizeBSphereCommand* pCmd;

	if (m_commands.empty())
	{
		pCmd = new VisualizeBSphereCommand(world, color);
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
void VisualizeBSphereCommandPool::RecycleCommand(VisualizeBSphereCommand* pCmd)
{
	m_commands.push(pCmd);
}
