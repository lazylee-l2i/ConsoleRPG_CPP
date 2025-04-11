#pragma once
#include "Utill.h"

class TimeManager
{
	DECLARE_SINGLE(TimeManager);
private:
	double dStartLoop = 0;
	double dFrameTick = 0;

public:
	void Init();
	void LoopStart();
	void SetFrameTick(int Hz);
	int GetFrameCount();
	double GetFrameTickTime();
};