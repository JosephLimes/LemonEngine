#include "AlarmRegistrationCommand.h"
#include "GameObject/AlarmableAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* pAlarmable, AlarmableManager::AlarmID id)
	: m_pAlarmable(pAlarmable), m_ID(id) {}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::Register(m_pAlarmable, m_ID, m_triggerTime);
}

void AlarmRegistrationCommand::SetTime(float time)
{
	m_triggerTime = time;
}
