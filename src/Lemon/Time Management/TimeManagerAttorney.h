#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
public:
	friend class Lemon;

	TimeManagerAttorney() = delete;
	TimeManagerAttorney(const TimeManagerAttorney&) = delete;
	TimeManagerAttorney& operator = (const TimeManagerAttorney&) = delete;
	~TimeManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { TimeManager::Terminate(); }
	static void			ProcessTime() { TimeManager::ProcessTime(); }
};

#endif _TimeManagerAttorney