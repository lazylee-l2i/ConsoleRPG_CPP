#pragma once
#include <iostream>
#include <thread>

#include <vector>
#include <map>

#include <Windows.h>
#include <random>

#include <conio.h>

#include "Actor.h"
#include "Type.h"
#include "Item.h"
#include "GameTimer.h"
#include "Manager.h"

int iRandNum(int N);

bool bBoundaryCheck(Pos& pos, int sizeX, int sizeY);