#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "Command.h"
#include "Scene/AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public Command
{
public:
	AlarmDeregistrationCommand(Alarmable* pAlarmable, AlarmableManager::AlarmID id);
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator = (const AlarmDeregistrationCommand&) = delete;
	~AlarmDeregistrationCommand() = default;

private:
	Alarmable*					m_pAlarmable;
	AlarmableManager::AlarmID	m_ID;

public:
	void						Execute() override;
};

#endif _AlarmDeregistrationCommand