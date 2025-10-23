#ifndef _LemonAttorney
#define _LemonAttorney

#include "Lemon.h"

class LemonAttorney
{
public:
	friend class FreezeTime;

	LemonAttorney() = delete;
	LemonAttorney(const LemonAttorney&) = delete;
	LemonAttorney& operator = (const LemonAttorney&) = delete;
	~LemonAttorney() = delete;

private:
	// passthrough for freezetime
	static float		GetTime() { return Lemon::GetTime(); };

};

#endif _LemonAttorney