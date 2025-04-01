#include "GameTimer.h"
#include <time.h>

void GameTimer::LoopStart()
{
	this->dStartLoop = (double)clock();
}

void GameTimer::SetFrameTick(int Hz)
{
	this->dFrameTick = static_cast<double>(1000) / Hz;
}

int GameTimer::GetFrameCount()
{
	int count = (static_cast<double>(clock()) - this->dStartLoop) / this->dFrameTick;
	return count;
}

double GameTimer::GetFrameTickTime()
{
	return this->dFrameTick;
}
