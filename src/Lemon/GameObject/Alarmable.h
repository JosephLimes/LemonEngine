#ifndef _Alarmable
#define _Alarmable

#include "GameObject/RegistrationState.h"
#include "Scene/AlarmableManager.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;

public:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator = (const Alarmable&) = delete;
	virtual ~Alarmable();

private:
	struct AlarmData
	{
		AlarmableManager::ListRef	m_listRef;
		RegistrationState			m_regState;
		AlarmRegistrationCommand*	m_pRegisterCommand;
		AlarmDeregistrationCommand* m_pDeregisterCommand;
	};
	// Registration data for each alarm
	AlarmData						m_alarms[AlarmableManager::ALARM_COUNT];

	// Reference for fast removal from list in AlarmableManager
	AlarmableManager::ListRef		m_listRef;

public:
	void							SubmitRegistration(AlarmableManager::AlarmID id, float time);
	void							SubmitDeregistration(AlarmableManager::AlarmID id);

private:
	virtual void					Alarm0() {};
	virtual void					Alarm1() {};
	virtual void					Alarm2() {};

	void							TriggerAlarm(AlarmableManager::AlarmID id);
	void							Register(AlarmableManager::AlarmID id, float time);
	void							Deregister(AlarmableManager::AlarmID id);
};

#endif _Alarmable