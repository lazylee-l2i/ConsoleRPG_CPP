#pragma once
#include "Utill.h"

#include <chrono>

class TimeManager
{
	DECLARE_SINGLE(TimeManager);
private:
	double dStartLoop = 0;
	double dFrameTick = 0;
public:
	void Init();
	// Clock Start
	void LoopStart();
	// Setting FPS
	void SetFrameTick(int Hz);
	// Calculate Frame Count using current clock
	int GetFrameCount();
	// Get Current Frame Tick Time => 1 sec / FPS __ double
	double GetFrameTickTime();
};