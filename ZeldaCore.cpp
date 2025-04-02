#include "ZeldaCore.h"

int iRandNum(int N)
{
	srand(static_cast<unsigned int>(GetTickCount64()));
	Sleep(1);
	return (rand() % N);
}

