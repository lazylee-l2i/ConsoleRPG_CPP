#pragma once


class GameTimer
{
private:
	double dStartLoop;
	double dFrameTick;

public:
	void LoopStart();
	void SetFrameTick(int Hz);
};