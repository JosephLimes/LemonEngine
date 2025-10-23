#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

class GameObjectAttorney
{
public:
	GameObjectAttorney() = delete;
	GameObjectAttorney(const GameObjectAttorney&) = delete;
	GameObjectAttorney& operator = (const GameObjectAttorney&) = delete;
	~GameObjectAttorney() = delete;

private:
		friend class		GameObjectRegistrationCommand;
		friend class		GameObjectDeregistrationCommand;
		static void			Register(GameObject* pObj) { pObj->ConnectToScene(); }
		static void			Deregister(GameObject* pObj) { pObj->DisconnectFromScene(); }
};

#endif _GameObjectAttorney