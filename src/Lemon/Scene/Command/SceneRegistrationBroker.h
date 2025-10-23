#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <queue>

class Command;

class SceneRegistrationBroker
{
public:
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator = (const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() = default;

private:
	std::queue<Command*>		m_commandQueue;

public:
	void						AddCommand(Command* pCmd);
	void						ExecuteCommands();

};

#endif _SceneRegistrationBroker