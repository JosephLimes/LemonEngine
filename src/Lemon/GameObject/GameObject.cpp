#include "GameObject.h"
#include "Scene/Command/GameObjectRegistrationCommand.h"
#include "Scene/Command/GameObjectDeregistrationCommand.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

GameObject::GameObject()
	:	m_registerState(RegistrationState::CURRENTLY_DEREGISTERED),
		m_pRegisterCommand(new GameObjectRegistrationCommand(this)),
		m_pDeregisterCommand(new GameObjectDeregistrationCommand(this))
{}

GameObject::~GameObject()
{
	delete m_pRegisterCommand;
	delete m_pDeregisterCommand;
}

void GameObject::SubmitEntry()
{
	assert(m_registerState == RegistrationState::CURRENTLY_DEREGISTERED);
	m_registerState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetActiveScene().SubmitCommand(m_pRegisterCommand);
}

void GameObject::SubmitExit()
{
	if (m_registerState == RegistrationState::PENDING_DEREGISTRATION)
	{
		// object already pending exit, ignore call
		return;
	}

	assert(m_registerState == RegistrationState::CURRENTLY_REGISTERED);
	m_registerState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetActiveScene().SubmitCommand(m_pDeregisterCommand);
}

void GameObject::ConnectToScene()
{
	assert(m_registerState == RegistrationState::PENDING_REGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_REGISTERED;
	SceneEntry();
}

void GameObject::DisconnectFromScene()
{
	assert(m_registerState == RegistrationState::PENDING_DEREGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_DEREGISTERED;
	SceneExit();
}
