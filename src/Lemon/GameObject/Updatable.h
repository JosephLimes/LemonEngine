#ifndef _Updatable
#define _Updatable

#include "GameObject/RegistrationState.h"
#include "Scene/UpdatableManager.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
	friend class UpdatableAttorney;

public:
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator = (const Updatable&) = delete;
	virtual ~Updatable();

private:
	// Registration/deregistration
	RegistrationState				m_registerState;
	UpdateRegistrationCommand*		m_pRegisterCommand;
	UpdateDeregistrationCommand*	m_pDeregisterCommand;

	// Reference for fast removal from list in UpdatableManager
	UpdatableManager::ListRef		m_listRef;

public:
	void							SubmitRegistration();
	void							SubmitDeregistration();

private:
	virtual void					Update() {};

	void							Register();
	void							Deregister();
};

#endif _Updatable