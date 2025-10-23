#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"

class InputableAttorney
{
public:
	InputableAttorney() = delete;
	InputableAttorney(const InputableAttorney&) = delete;
	InputableAttorney& operator = (const InputableAttorney&) = delete;
	~InputableAttorney() = delete;

	class GameLoop
	{
	private:
		friend class		KeyManager;
		friend class		KeyboardInputManager;
		friend class		ButtonManager;
		static void			KeyPressed(Inputable* pObj, AZUL_KEY key) { pObj->KeyPressed(key); };
		static void			KeyReleased (Inputable* pObj, AZUL_KEY key) { pObj->KeyReleased(key); };
		static void			KeyTyped(Inputable* pObj, char c) { pObj->KeyTyped(c); }
		static void			MousePressed(Inputable* pObj, AZUL_MOUSE button) { pObj->MousePressed(button); }
		static void			MouseReleased(Inputable* pObj, AZUL_MOUSE button) { pObj->MouseReleased(button); }
	};

	class Registration
	{
	private:
		friend class		InputRegistrationCommand;
		friend class		InputDeregistrationCommand;
		friend class		InputTypedRegistrationCommand;
		friend class		InputTypedDeregistrationCommand;
		friend class		InputMouseRegistrationCommand;
		friend class		InputMouseDeregistrationCommand;
		static void			Register(Inputable* pObj, AZUL_KEY key, KeyEvent event) { pObj->Register(key, event); }
		static void			Deregister(Inputable* pObj, AZUL_KEY key, KeyEvent event) { pObj->Deregister(key, event); }
		static void			Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event) { pObj->Register(button, event); }
		static void			Deregister(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event) { pObj->Deregister(button, event); }
		static void			RegisterTyped(Inputable* pObj) { pObj->RegisterTyped(); }
		static void			DeregisterTyped(Inputable* pObj) { pObj->DeregisterTyped(); }
	};
};

#endif _InputableAttorney