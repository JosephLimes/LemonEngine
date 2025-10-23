#include "Updatable.h"
#include "Scene/SceneManager.h"
#include "Scene/Command/UpdateRegistrationCommand.h"
#include "Scene/Command/UpdateDeregistrationCommand.h"
#include "Scene/SceneAttorney.h"

Updatable::Updatable()
	:	m_registerState(RegistrationState::CURRENTLY_DEREGISTERED),
		m_pRegisterCommand(new UpdateRegistrationCommand(this)),
		m_pDeregisterCommand(new UpdateDeregistrationCommand(this))
{}

Updatable::~Updatable()
{
	delete m_pRegisterCommand;
	delete m_pDeregisterCommand;
}

void Updatable::SubmitRegistration()
{
	// Submit an update registration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_DEREGISTERED);
	m_registerState = RegistrationState::PENDING_REGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pRegisterCommand);
}

void Updatable::SubmitDeregistration()
{
	// Submit an update deregistration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_REGISTERED);
	m_registerState = RegistrationState::PENDING_DEREGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pDeregisterCommand);
}

void Updatable::Register()
{
	// Register to scene

	assert(m_registerState == RegistrationState::PENDING_REGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Register(this, m_listRef);
}

void Updatable::Deregister()
{
	// Deregister from scene

	assert(m_registerState == RegistrationState::PENDING_DEREGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Deregister(m_listRef);
}
