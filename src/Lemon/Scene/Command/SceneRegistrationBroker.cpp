#include "SceneRegistrationBroker.h"
#include "Command.h"

void SceneRegistrationBroker::AddCommand(Command* pCmd)
{
	m_commandQueue.push(pCmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	while (!m_commandQueue.empty())
	{
		m_commandQueue.front()->Execute();
		m_commandQueue.pop();
	}
}
