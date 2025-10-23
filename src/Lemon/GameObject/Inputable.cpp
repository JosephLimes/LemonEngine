#include "Inputable.h"
#include "Scene/Command/Input/InputRegistrationCommand.h"
#include "Scene/Command/Input/InputDeregistrationCommand.h"
#include "Scene/Command/Input/InputTypedRegistrationCommand.h"
#include "Scene/Command/Input/InputTypedDeregistrationCommand.h"
#include "Scene/Command/Input/InputMouseRegistrationCommand.h"
#include "Scene/Command/Input/InputMouseDeregistrationCommand.h"
#include "Scene/KeyboardInputManager.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneAttorney.h"

Inputable::Inputable()
	:	m_typedRegState(RegistrationState::CURRENTLY_DEREGISTERED), 
		m_typedRegisterCommand(new InputTypedRegistrationCommand(this)), 
		m_typedDeregisterCommand(new InputTypedDeregistrationCommand(this)),
		m_mouseRegState(RegistrationState::CURRENTLY_DEREGISTERED)
{}

Inputable::~Inputable()
{
	delete m_typedRegisterCommand;
	delete m_typedDeregisterCommand;

	std::map<AZUL_KEY, KeyData>::iterator it;
	for (it = m_keys.begin(); it != m_keys.end(); it++)
	{
		delete it->second.m_pPressRegisterCommand;
		delete it->second.m_pPressDeregisterCommand;
		delete it->second.m_pReleaseRegisterCommand;
		delete it->second.m_pReleaseDeregisterCommand;
	}

	std::map<AZUL_MOUSE, ButtonData>::iterator it2;
	for (it2 = m_buttons.begin(); it2 != m_buttons.end(); it2++)
	{
		delete it2->second.m_pPressRegisterCommand;
		delete it2->second.m_pPressDeregisterCommand;
		delete it2->second.m_pReleaseRegisterCommand;
		delete it2->second.m_pReleaseDeregisterCommand;
	}
}

void Inputable::SubmitRegistration(AZUL_KEY key, KeyEvent event)
{
	std::map<AZUL_KEY, KeyData>::iterator it = m_keys.find(key);

	if (it == m_keys.end()) // key has never been registered, create data
	{
		KeyData data;

		data.m_pressRegState = RegistrationState::CURRENTLY_DEREGISTERED;
		data.m_pPressRegisterCommand = new InputRegistrationCommand(this, key, KeyEvent::KEY_PRESS);
		data.m_pPressDeregisterCommand = new InputDeregistrationCommand(this, key, KeyEvent::KEY_PRESS);

		data.m_releaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;
		data.m_pReleaseRegisterCommand = new InputRegistrationCommand(this, key, KeyEvent::KEY_RELEASE);
		data.m_pReleaseDeregisterCommand = new InputDeregistrationCommand(this, key, KeyEvent::KEY_RELEASE);

		it = m_keys.insert(m_keys.end(), std::pair<AZUL_KEY, KeyData>(key, data));
	}

	switch (event)
	{
		case KeyEvent::KEY_PRESS:
			assert(it->second.m_pressRegState == RegistrationState::CURRENTLY_DEREGISTERED);
			it->second.m_pressRegState = RegistrationState::PENDING_REGISTRATION;
			// submit reg
			SceneManager::GetActiveScene().SubmitCommand(it->second.m_pPressRegisterCommand);
			break;
		case KeyEvent::KEY_RELEASE:
			assert(it->second.m_releaseRegState == RegistrationState::CURRENTLY_DEREGISTERED);
			it->second.m_releaseRegState = RegistrationState::PENDING_REGISTRATION;
			// submit reg
			SceneManager::GetActiveScene().SubmitCommand(it->second.m_pReleaseRegisterCommand);
			break;
	}
}

void Inputable::SubmitDeregistration(AZUL_KEY key, KeyEvent event)
{
	std::map<AZUL_KEY, KeyData>::iterator it = m_keys.find(key);

	switch (event)
	{
	case KeyEvent::KEY_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::CURRENTLY_REGISTERED);
		it->second.m_pressRegState = RegistrationState::PENDING_DEREGISTRATION;
		// submit dereg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pPressDeregisterCommand);
		break;
	case KeyEvent::KEY_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::CURRENTLY_REGISTERED);
		it->second.m_releaseRegState = RegistrationState::PENDING_DEREGISTRATION;
		// submit dereg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pReleaseDeregisterCommand);
		break;
	}
}

void Inputable::SubmitRegistrationTyped()
{
	assert(m_typedRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	m_typedRegState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetActiveScene().SubmitCommand(m_typedRegisterCommand);
}

void Inputable::SubmitDeregistrationTyped()
{
	assert(m_typedRegState == RegistrationState::CURRENTLY_REGISTERED);
	m_typedRegState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetActiveScene().SubmitCommand(m_typedDeregisterCommand);
}

void Inputable::SubmitRegistration(AZUL_MOUSE button, ButtonEvent event)
{
	std::map<AZUL_MOUSE, ButtonData>::iterator it = m_buttons.find(button);

	if (it == m_buttons.end()) // key has never been registered, create data
	{
		ButtonData data;

		data.m_pressRegState = RegistrationState::CURRENTLY_DEREGISTERED;
		data.m_pPressRegisterCommand = new InputMouseRegistrationCommand(this, button, ButtonEvent::BUTTON_PRESS);
		data.m_pPressDeregisterCommand = new InputMouseDeregistrationCommand(this, button, ButtonEvent::BUTTON_PRESS);

		data.m_releaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;
		data.m_pReleaseRegisterCommand = new InputMouseRegistrationCommand(this, button, ButtonEvent::BUTTON_RELEASE);
		data.m_pReleaseDeregisterCommand = new InputMouseDeregistrationCommand(this, button, ButtonEvent::BUTTON_RELEASE);

		it = m_buttons.insert(m_buttons.end(), std::pair<AZUL_MOUSE, ButtonData>(button, data));
	}

	switch (event)
	{
	case ButtonEvent::BUTTON_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::CURRENTLY_DEREGISTERED);
		it->second.m_pressRegState = RegistrationState::PENDING_REGISTRATION;
		// submit reg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pPressRegisterCommand);
		break;
	case ButtonEvent::BUTTON_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::CURRENTLY_DEREGISTERED);
		it->second.m_releaseRegState = RegistrationState::PENDING_REGISTRATION;
		// submit reg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pReleaseRegisterCommand);
		break;
	}
}

void Inputable::SubmitDeregistration(AZUL_MOUSE button, ButtonEvent event)
{
	std::map<AZUL_MOUSE, ButtonData>::iterator it = m_buttons.find(button);

	switch (event)
	{
	case ButtonEvent::BUTTON_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::CURRENTLY_REGISTERED);
		it->second.m_pressRegState = RegistrationState::PENDING_DEREGISTRATION;
		// submit dereg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pPressDeregisterCommand);
		break;
	case ButtonEvent::BUTTON_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::CURRENTLY_REGISTERED);
		it->second.m_releaseRegState = RegistrationState::PENDING_DEREGISTRATION;
		// submit dereg
		SceneManager::GetActiveScene().SubmitCommand(it->second.m_pReleaseDeregisterCommand);
		break;
	}
}

void Inputable::Register(AZUL_KEY key, KeyEvent event)
{
	std::map<AZUL_KEY, KeyData>::iterator it = m_keys.find(key);

	switch (event) // to send the correct listRef
	{
	case KeyEvent::KEY_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::PENDING_REGISTRATION);
		it->second.m_pressRegState = RegistrationState::CURRENTLY_REGISTERED;

		SceneAttorney::Register(this, key, event, it->second.m_pressListRef);
		break;
	case KeyEvent::KEY_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::PENDING_REGISTRATION);
		it->second.m_releaseRegState = RegistrationState::CURRENTLY_REGISTERED;

		SceneAttorney::Register(this, key, event, it->second.m_releaseListRef);
		break;
	}
}

void Inputable::Deregister(AZUL_KEY key, KeyEvent event)
{
	std::map<AZUL_KEY, KeyData>::iterator it = m_keys.find(key);

	switch (event) // to send the correct listRef
	{
	case KeyEvent::KEY_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::PENDING_DEREGISTRATION);
		it->second.m_pressRegState = RegistrationState::CURRENTLY_DEREGISTERED;

		SceneAttorney::Deregister(key, event, it->second.m_pressListRef);
		break;
	case KeyEvent::KEY_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::PENDING_DEREGISTRATION);
		it->second.m_releaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;

		SceneAttorney::Deregister(key, event, it->second.m_releaseListRef);
		break;
	}
}

void Inputable::RegisterTyped()
{
	assert(m_typedRegState == RegistrationState::PENDING_REGISTRATION);

	SceneAttorney::RegisterTyped(this, m_typedListRef);
}

void Inputable::DeregisterTyped()
{
	assert(m_typedRegState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::DeregisterTyped(m_typedListRef);
}

void Inputable::Register(AZUL_MOUSE button, ButtonEvent event)
{
	std::map<AZUL_MOUSE, ButtonData>::iterator it = m_buttons.find(button);

	switch (event) // to send the correct listRef
	{
	case ButtonEvent::BUTTON_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::PENDING_REGISTRATION);
		it->second.m_pressRegState = RegistrationState::CURRENTLY_REGISTERED;

		SceneAttorney::Register(this, button, event, it->second.m_pressListRef);
		break;
	case ButtonEvent::BUTTON_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::PENDING_REGISTRATION);
		it->second.m_releaseRegState = RegistrationState::CURRENTLY_REGISTERED;

		SceneAttorney::Register(this, button, event, it->second.m_releaseListRef);
		break;
	}
}

void Inputable::Deregister(AZUL_MOUSE button, ButtonEvent event)
{
	std::map<AZUL_MOUSE, ButtonData>::iterator it = m_buttons.find(button);

	switch (event) // to send the correct listRef
	{
	case ButtonEvent::BUTTON_PRESS:
		assert(it->second.m_pressRegState == RegistrationState::PENDING_DEREGISTRATION);
		it->second.m_pressRegState = RegistrationState::CURRENTLY_DEREGISTERED;

		SceneAttorney::Deregister(button, event, it->second.m_pressListRef);
		break;
	case ButtonEvent::BUTTON_RELEASE:
		assert(it->second.m_releaseRegState == RegistrationState::PENDING_DEREGISTRATION);
		it->second.m_releaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;

		SceneAttorney::Deregister(button, event, it->second.m_releaseListRef);
		break;
	}
}
