#include "GameObjectDeregistrationCommand.h"
#include "GameObject/GameObjectAttorney.h"

GameObjectDeregistrationCommand::GameObjectDeregistrationCommand(GameObject* pGameObject)
	: m_pGameObject(pGameObject) {}

void GameObjectDeregistrationCommand::Execute()
{
	GameObjectAttorney::Deregister(m_pGameObject);
}
