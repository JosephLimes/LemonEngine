#ifndef _Drawable
#define _Drawable

#include "GameObject/RegistrationState.h"
#include "Scene/DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
	friend class DrawableAttorney;

public:
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator = (const Drawable&) = delete;
	virtual ~Drawable();

private:
	// Registration/deregistration
	RegistrationState				m_registerState;
	DrawRegistrationCommand*		m_pRegisterCommand;
	DrawDeregistrationCommand*		m_pDeregisterCommand;

	// Reference for fast removal from list in UpdatableManager
	DrawableManager::ListRef		m_listRef;

public:
	void							SubmitRegistration();
	void							SubmitDeregistration();

private:
	virtual void					Draw2D() {};
	virtual void					Draw3D() {};

	virtual void					DrawEditor2D();
	virtual void					DrawEditor3D();

	void							Register();
	void							Deregister();
};

#endif _Drawable