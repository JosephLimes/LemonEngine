#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

class Alarmable;

class AlarmableManager
{
public:
	// IDs for individual alarm callbacks
	enum class AlarmID
	{
		ALARM_0,
		ALARM_1,
		ALARM_2
	};

	// Type for Alarmables to store a reference in our list
	using ListRef = std::multimap<float, std::pair<Alarmable*, AlarmID>>::iterator;

	static const int ALARM_COUNT = 3;

	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator = (const AlarmableManager&) = delete;
	~AlarmableManager() = default;

private:
	using AlarmEvent = std::pair<Alarmable*, AlarmID>;
	using AlarmMap = std::multimap<float, AlarmEvent>;
	AlarmMap							m_registeredAlarms;

public:
	void								Register(float time, Alarmable* pAlarmable, AlarmID id, ListRef& ref);
	void								Deregister(const ListRef& ref);
	void								ProcessElements();

};

#endif _AlarmableManager