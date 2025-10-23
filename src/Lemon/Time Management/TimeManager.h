#ifndef _TimeManager
#define _TimeManager

#include "AzulCore.h"

class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;

private: 
	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator = (const TimeManager&) = delete;
	~TimeManager();

	static TimeManager*					m_pInstance;
	float								m_currentTime;
	float								m_frameTime;
	float								m_previousTime;
	FreezeTime*							m_pFreezeTime;

	static TimeManager&					Instance();

public:
	static float						GetTime();
	static float						GetFrameTime();

private:
	static void							Terminate();
	static void							ProcessTime() { Instance().privProcessTime(); };
	void								privProcessTime();
};

#endif _TimeManager