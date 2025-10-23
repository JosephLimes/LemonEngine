#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

class ScreenLogAttorney
{
public:
	friend class Lemon;

	ScreenLogAttorney() = delete;
	ScreenLogAttorney(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney& operator = (const ScreenLogAttorney&) = delete;
	~ScreenLogAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { ScreenLog::Terminate(); }
	static void			Render() { ScreenLog::Render(); }
};

#endif _ScreenLogAttorney