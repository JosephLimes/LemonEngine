#include "Drawable.h"
#include "Scene/SceneManager.h"
#include "Scene/Command/DrawRegistrationCommand.h"
#include "Scene/Command/DrawDeregistrationCommand.h"
#include "Scene/SceneAttorney.h"

Drawable::Drawable()
	:	m_registerState(RegistrationState::CURRENTLY_DEREGISTERED),
		m_pRegisterCommand(new DrawRegistrationCommand(this)),
		m_pDeregisterCommand(new DrawDeregistrationCommand(this))
{}

Drawable::~Drawable()
{
	delete m_pRegisterCommand;
	delete m_pDeregisterCommand;
}

void Drawable::SubmitRegistration()
{
	// Submit a Draw registration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_DEREGISTERED);
	m_registerState = RegistrationState::PENDING_REGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pRegisterCommand);
}

void Drawable::SubmitDeregistration()
{
	// Submit a Draw deregistration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_REGISTERED);
	m_registerState = RegistrationState::PENDING_DEREGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pDeregisterCommand);
}

void Drawable::DrawEditor2D()
{
	// default unoverloaded behavior just calls the normal functions
	Draw2D();
}

void Drawable::DrawEditor3D()
{
	// default unoverloaded behavior just calls the normal functions
	Draw3D();
}

void Drawable::Register()
{
	// Register to scene (called from commands sent to scene)

	assert(m_registerState == RegistrationState::PENDING_REGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Register(this, m_listRef);
}

void Drawable::Deregister()
{
	// Deregister from scene (called from commands sent to scene)

	assert(m_registerState == RegistrationState::PENDING_DEREGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Deregister(m_listRef);
}
