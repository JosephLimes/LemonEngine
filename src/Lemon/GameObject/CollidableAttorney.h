#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	CollidableAttorney() = delete;
	CollidableAttorney(const CollidableAttorney&) = delete;
	CollidableAttorney& operator = (const CollidableAttorney&) = delete;
	~CollidableAttorney() = delete;

	class GameLoop
	{
	private:
		friend class		CollisionManager;
		//static void			Collide(Collidable* pObj) { pObj->Collide(); };
	};

	class Registration
	{
	private:
		friend class		CollideRegistrationCommand;
		friend class		CollideDeregistrationCommand;
		static void			Register(Collidable* pObj) { pObj->Register(); }
		static void			Deregister(Collidable* pObj) { pObj->Deregister(); }
	};
};

#endif _CollidableAttorney