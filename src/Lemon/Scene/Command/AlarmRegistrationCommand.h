#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "Command.h"
#include "Scene/AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public Command
{
public:
	AlarmRegistrationCommand(Alarmable* pAlarmable, AlarmableManager::AlarmID id);
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator = (const AlarmRegistrationCommand&) = delete;
	~AlarmRegistrationCommand() = default;

private:
	Alarmable*					m_pAlarmable;
	AlarmableManager::AlarmID	m_ID;
	float						m_triggerTime;

public:
	void						Execute() override;
	void						SetTime(float time);
};

#endif _AlarmRegistrationCommand