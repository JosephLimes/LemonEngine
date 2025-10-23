// FreezeTime
// Andre Berthiaume, Jan 2022

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;

	static const float DEAD_TIME_THRESHOLD;
	const float DEFAULT_FRAME_TIME;  // Not static since automatically adjusted to monitor's refesh rate

	float totalFrozenTime;
	bool freeze_mode_active;

	bool HackedKeyRelease(AZUL_KEY k);
	void TestForFreezeKeys();

	DWORD FreezeTime::GetRefreshRate();

public:
	FreezeTime();
	~FreezeTime() {};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float ComputeGameTime(float prev_time);
};

#endif _FreezeTime