#pragma once
#include "Type.h"

#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct Pos;

class InputManager
{
	DECLARE_SINGLE(InputManager);
private:
	bool AttackKey = false;
public:
	EInputType PlayerInput();
	EInputType MonsterInput();
	int GetRandomNum(int n);
	Pos GetRandomPos();
	bool IsAttackKeyPressed();
	void AttackKeyRelease();
};

