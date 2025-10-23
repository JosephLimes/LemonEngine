#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
	AlarmableAttorney() = delete;
	AlarmableAttorney(const AlarmableAttorney&) = delete;
	AlarmableAttorney& operator = (const AlarmableAttorney&) = delete;
	~AlarmableAttorney() = delete;

	class GameLoop
	{
	private:
		friend class		AlarmableManager;
		static void			TriggerAlarm(Alarmable* pObj, AlarmableManager::AlarmID id) { pObj->TriggerAlarm(id); };
	};

	class Registration
	{
	private:
		friend class		AlarmRegistrationCommand;
		friend class		AlarmDeregistrationCommand;
		static void			Register(Alarmable* pObj, AlarmableManager::AlarmID id, float time) { pObj->Register(id, time); }
		static void			Deregister(Alarmable* pObj, AlarmableManager::AlarmID id) { pObj->Deregister(id); }
	};
};

#endif _AlarmableAttorney