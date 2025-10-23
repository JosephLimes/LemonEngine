#include "GameObjectRegistrationCommand.h"
#include "GameObject/GameObjectAttorney.h"

GameObjectRegistrationCommand::GameObjectRegistrationCommand(GameObject* pGameObject)
	: m_pGameObject(pGameObject) {}

void GameObjectRegistrationCommand::Execute()
{
	GameObjectAttorney::Register(m_pGameObject);
}
