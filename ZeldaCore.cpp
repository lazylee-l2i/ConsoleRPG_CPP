#include "ZeldaCore.h"

int iRandNum(int N)
{
	srand(static_cast<unsigned int>(GetTickCount64()));
	Sleep(1);
	return (rand() % N);
}

bool bBoundaryCheck(Pos& pos, int sizeX, int sizeY)
{
	if (pos.x < 0)
	{
		pos.x = 0;
		return false;
	}
	else if (pos.x > 9)
	{
		pos.x = 9;
		return false;
	}
	if (pos.y < 0)
	{
		pos.y = 0;
		return false;
	}
	else if (pos.y > 4)
	{
		pos.x = 4;
		return false;
	}

	return true;
}
