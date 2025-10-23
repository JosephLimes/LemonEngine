#include "AlarmableManager.h"
#include "GameObject/AlarmableAttorney.h"
#include "..\Lemon.h"
#include "Time Management/TimeManager.h"

void AlarmableManager::Register(float time, Alarmable* pAlarmable, AlarmID id, ListRef& ref)
{
	AlarmEvent event = std::pair<Alarmable*, AlarmID>(pAlarmable, id);
	ref = m_registeredAlarms.insert( std::pair<float, AlarmEvent>(time, event) );
}

void AlarmableManager::Deregister(const ListRef& ref)
{
	m_registeredAlarms.erase(ref);
}

void AlarmableManager::ProcessElements()
{
	ListRef it = m_registeredAlarms.begin();
	ListRef del;
	while (it != m_registeredAlarms.end() && it->first < TimeManager::GetTime())
	{
		AlarmableAttorney::GameLoop::TriggerAlarm(it->second.first, it->second.second);
		del = it;
		it++;
		m_registeredAlarms.erase(del);
	}
}
