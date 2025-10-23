#ifndef _Inputable
#define _Inputable

#include <map>

#include "AzulCore.h"

#include "GameObject/RegistrationState.h"
#include "GameObject/InputTypes.h"
#include "Scene/KeyboardInputManager.h"
#include "Scene/MouseInputManager.h"

class InputRegistrationCommand;
class InputDeregistrationCommand;
class InputTypedRegistrationCommand;
class InputTypedDeregistrationCommand;
class InputMouseRegistrationCommand;
class InputMouseDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;

public:
	Inputable();
	Inputable(const Inputable&) = delete;
	Inputable& operator = (const Inputable&) = delete;
	virtual ~Inputable();

private:
	struct KeyData
	{
		// Associated key
		AZUL_KEY						m_key;

		// Press data
		KeyboardInputManager::ListRef	m_pressListRef;
		RegistrationState				m_pressRegState;
		InputRegistrationCommand*		m_pPressRegisterCommand;
		InputDeregistrationCommand*		m_pPressDeregisterCommand;

		// Release data
		KeyboardInputManager::ListRef	m_releaseListRef;
		RegistrationState				m_releaseRegState;
		InputRegistrationCommand*		m_pReleaseRegisterCommand;
		InputDeregistrationCommand*		m_pReleaseDeregisterCommand;
	};

	struct ButtonData
	{
		// Associated button
		AZUL_MOUSE							m_button;

		// Press data
		MouseInputManager::ListRef			m_pressListRef;
		RegistrationState					m_pressRegState;
		InputMouseRegistrationCommand*		m_pPressRegisterCommand;
		InputMouseDeregistrationCommand*	m_pPressDeregisterCommand;

		// Release data
		MouseInputManager::ListRef			m_releaseListRef;
		RegistrationState					m_releaseRegState;
		InputMouseRegistrationCommand*		m_pReleaseRegisterCommand;
		InputMouseDeregistrationCommand*	m_pReleaseDeregisterCommand;
	};

	std::map<AZUL_KEY, KeyData>			m_keys;
	std::map<AZUL_MOUSE, ButtonData>	m_buttons;

	RegistrationState					m_typedRegState;
	KeyboardInputManager::ListRef		m_typedListRef;
	InputTypedRegistrationCommand*		m_typedRegisterCommand;
	InputTypedDeregistrationCommand*	m_typedDeregisterCommand;

	RegistrationState					m_mouseRegState;

	InputMouseRegistrationCommand*		m_mouseRegisterCommand;
	InputMouseDeregistrationCommand*	m_mouseDeregisterCommand;

public:

	void								SubmitRegistration(AZUL_KEY key, KeyEvent event);
	void								SubmitDeregistration(AZUL_KEY key, KeyEvent event);

	void								SubmitRegistrationTyped();
	void								SubmitDeregistrationTyped();

	void								SubmitRegistration(AZUL_MOUSE button, ButtonEvent event);
	void								SubmitDeregistration(AZUL_MOUSE button, ButtonEvent event);

private:
	// Registration
	void								Register(AZUL_KEY key, KeyEvent event);
	void								Deregister(AZUL_KEY key, KeyEvent event);

	void								RegisterTyped();
	void								DeregisterTyped();

	void								Register(AZUL_MOUSE button, ButtonEvent event);
	void								Deregister(AZUL_MOUSE button, ButtonEvent event);

	virtual void						KeyPressed(AZUL_KEY key) { key; };
	virtual void						KeyReleased(AZUL_KEY key) { key; };
	virtual void						KeyTyped(char c) { c; };
	virtual void						MousePressed(AZUL_MOUSE button) { button; };
	virtual void						MouseReleased(AZUL_MOUSE button) { button; };
};

#endif _Inputable