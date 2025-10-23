#include "AlarmDeregistrationCommand.h"
#include "GameObject/AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* pAlarmable, AlarmableManager::AlarmID id)
	: m_pAlarmable(pAlarmable), m_ID(id) {}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::Deregister(m_pAlarmable, m_ID);
}
