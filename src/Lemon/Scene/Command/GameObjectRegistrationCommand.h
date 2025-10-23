#ifndef _GameObjectRegistrationCommand
#define _GameObjectRegistrationCommand

#include "Command.h"

class GameObject;

class GameObjectRegistrationCommand : public Command
{
public:
	GameObjectRegistrationCommand(GameObject* pGameObject);
	GameObjectRegistrationCommand() = delete;
	GameObjectRegistrationCommand(const GameObjectRegistrationCommand&) = delete;
	GameObjectRegistrationCommand& operator = (const GameObjectRegistrationCommand&) = delete;
	~GameObjectRegistrationCommand() = default;

private:
	GameObject*				m_pGameObject;

public:
	void					Execute() override;
};

#endif _GameObjectRegistrationCommand