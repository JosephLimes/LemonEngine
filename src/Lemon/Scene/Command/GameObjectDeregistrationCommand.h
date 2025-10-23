#ifndef _GameObjectDeregistrationCommand
#define _GameObjectDeregistrationCommand

#include "Command.h"

class GameObject;

class GameObjectDeregistrationCommand : public Command
{
public:
	GameObjectDeregistrationCommand(GameObject* pGameObject);
	GameObjectDeregistrationCommand() = delete;
	GameObjectDeregistrationCommand(const GameObjectDeregistrationCommand&) = delete;
	GameObjectDeregistrationCommand& operator = (const GameObjectDeregistrationCommand&) = delete;
	~GameObjectDeregistrationCommand() = default;

private:
	GameObject*				m_pGameObject;

public:
	void					Execute() override;
};

#endif _GameObjectDeregistrationCommand