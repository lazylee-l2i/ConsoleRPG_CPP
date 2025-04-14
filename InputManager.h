#pragma once
#include "Utill.h"

#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct Pos;

class InputManager
{
	DECLARE_SINGLE(InputManager)
private:
	// for detecting press, release
	bool AttackKey = false;
public:
	// Async Method, Get Player Input
	EInputType PlayerInput();
	// Monster Movement Declare, Monster Only Move 4-way(up, down, left, right)
	EInputType MonsterInput();

	// for Auto Generating System
	int GetRandomNum(int n);
	Pos GetRandomPos();

	// prevent multiple key press
	bool IsAttackKeyPressed();
	void AttackKeyRelease();
};

