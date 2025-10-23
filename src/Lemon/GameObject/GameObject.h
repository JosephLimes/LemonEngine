#ifndef _GameObject
#define _GameObject

#include "AzulCore.h"

#include "Alarmable.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "GameObject/RegistrationState.h"

class GameObjectRegistrationCommand;
class GameObjectDeregistrationCommand;

class GameObject : public Alarmable, public Drawable, public Updatable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;

public:
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator = (const GameObject&) = delete;
	virtual ~GameObject();

private:
	//commands and state
	RegistrationState					m_registerState;
	GameObjectRegistrationCommand*		m_pRegisterCommand;
	GameObjectDeregistrationCommand*	m_pDeregisterCommand;
	
public:
	void								SubmitEntry();
	void								SubmitExit();

private:
	virtual void						SceneEntry() {};
	virtual void						SceneExit() {};
	void								ConnectToScene();
	void								DisconnectFromScene();
};

#endif _GameObject