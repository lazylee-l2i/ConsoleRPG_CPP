#include "TimeManager.h"
#include <time.h>
#include <Windows.h>

void TimeManager::Init()
{
	srand(static_cast<unsigned int>(time(0)));
}

void TimeManager::LoopStart()
{
	this->dStartLoop = (double)clock();
}

void TimeManager::SetFrameTick(int Hz)
{
	this->dFrameTick = static_cast<double>(1000) / Hz;
}

int TimeManager::GetFrameCount()
{
	int count = (static_cast<double>(clock()) - this->dStartLoop) / this->dFrameTick;
	return count;
}

double TimeManager::GetFrameTickTime()
{
	return this->dFrameTick;
}
