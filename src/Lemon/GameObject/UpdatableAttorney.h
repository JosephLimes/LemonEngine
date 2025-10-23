#ifndef _UpdatableAttorney
#define _UpdatableAttorney

#include "Updatable.h"

class UpdatableAttorney
{
public:
	UpdatableAttorney() = delete;
	UpdatableAttorney(const UpdatableAttorney&) = delete;
	UpdatableAttorney& operator = (const UpdatableAttorney&) = delete;
	~UpdatableAttorney() = delete;

	class GameLoop
	{
	private:
		friend class		UpdatableManager;
		static void			Update(Updatable* pObj) { pObj->Update(); };
	};

	class Registration
	{
	private:
		friend class		UpdateRegistrationCommand;
		friend class		UpdateDeregistrationCommand;
		static void			Register(Updatable* pObj) { pObj->Register(); }
		static void			Deregister(Updatable* pObj) { pObj->Deregister(); }
	};
};

#endif _UpdatableAttorney