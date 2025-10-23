#include "Alarmable.h"
#include "../Lemon.h"
#include "Scene/SceneManager.h"
#include "Scene/Command/AlarmRegistrationCommand.h"
#include "Scene/Command/AlarmDeregistrationCommand.h"
#include "Scene/SceneAttorney.h"
#include "Time Management/TimeManager.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_COUNT; i++)
	{
		m_alarms[i].m_pRegisterCommand = new AlarmRegistrationCommand(this, static_cast<AlarmableManager::AlarmID>(i));
		m_alarms[i].m_pDeregisterCommand = new AlarmDeregistrationCommand(this, static_cast<AlarmableManager::AlarmID>(i));
		m_alarms[i].m_regState = RegistrationState::CURRENTLY_DEREGISTERED;
	}
}

Alarmable::~Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_COUNT; i++)
	{
		delete m_alarms[i].m_pRegisterCommand;
		delete m_alarms[i].m_pDeregisterCommand;
	}
}

// Submit an alarm registration request to the scene
void Alarmable::SubmitRegistration(AlarmableManager::AlarmID id, float time)
{
	AlarmData& alarm = m_alarms[static_cast<int>(id)];

	// Update registration state
	assert(alarm.m_regState == RegistrationState::CURRENTLY_DEREGISTERED);
	alarm.m_regState = RegistrationState::PENDING_REGISTRATION;

	// Update the registration command to have a trigger time of current time + given offset, then send to scene
	alarm.m_pRegisterCommand->SetTime(time + TimeManager::GetTime());
	SceneManager::GetActiveScene().SubmitCommand(alarm.m_pRegisterCommand);
}


// Submit an alarm deregistration request to the scene
void Alarmable::SubmitDeregistration(AlarmableManager::AlarmID id)
{
	AlarmData& alarm = m_alarms[static_cast<int>(id)];

	// Update registration state
	assert(alarm.m_regState == RegistrationState::CURRENTLY_REGISTERED);
	alarm.m_regState = RegistrationState::PENDING_DEREGISTRATION;

	// Send request to scene
	SceneManager::GetActiveScene().SubmitCommand(alarm.m_pDeregisterCommand);
}


void Alarmable::TriggerAlarm(AlarmableManager::AlarmID id)
{
	AlarmData& alarm = m_alarms[static_cast<int>(id)];

	// Update registration state
	assert(alarm.m_regState == RegistrationState::CURRENTLY_REGISTERED);
	alarm.m_regState = RegistrationState::CURRENTLY_DEREGISTERED;

	// Actually trigger alarm
	switch (id)
	{
		case AlarmableManager::AlarmID::ALARM_0:
			Alarm0();
			break;
		case AlarmableManager::AlarmID::ALARM_1:
			Alarm1();
			break;
		case AlarmableManager::AlarmID::ALARM_2:
			Alarm2();
			break;
	}
}


// Register to scene (called from commands sent to scene)
void Alarmable::Register(AlarmableManager::AlarmID id, float time)
{
	AlarmData& alarm = m_alarms[static_cast<int>(id)];

	// Update registration state
	assert(alarm.m_regState == RegistrationState::PENDING_REGISTRATION);
	alarm.m_regState = RegistrationState::CURRENTLY_REGISTERED;

	// Register to scene
	SceneAttorney::Register(time, this, id, alarm.m_listRef);
}


// Deregister from scene (called from commands sent to scene)
void Alarmable::Deregister(AlarmableManager::AlarmID id)
{
	AlarmData& alarm = m_alarms[static_cast<int>(id)];

	// Update registration state
	assert(alarm.m_regState == RegistrationState::PENDING_DEREGISTRATION);
	alarm.m_regState = RegistrationState::CURRENTLY_DEREGISTERED;

	// Deregister from scene
	SceneAttorney::Deregister(alarm.m_listRef);
}
