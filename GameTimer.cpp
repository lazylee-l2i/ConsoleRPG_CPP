#include "GameTimer.h"
#include <time.h>

void GameTimer::LoopStart()
{
	this->dStartLoop = (double)clock();
}

void GameTimer::SetFrameTick(int Hz)
{
	this->dFrameTick = 1000 / Hz;
}
