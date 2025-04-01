#pragma once
#include <string>

#include "Type.h"
using namespace std;

class Actor
{
	string name;
	Pos pos;
	DIRECTION moveDirection = DIRECTION::QUIT;
	int hp;
public:
	Actor(string Name, const Pos& pos, int hp)
	{
		this->name = Name;
		this->pos = pos;
		this->hp = hp;
	}

	Actor(string Name, const Pos& pos)
	{
		this->name = Name;
		this->pos = pos;
		this->hp = 5;
	}

	Actor()
	{
		name = "";
		pos = Pos();
		hp = 0;
	}

	~Actor() {}

	DIRECTION GetDirection() { return this->moveDirection; }
	void SetDirection(DIRECTION dir) { this->moveDirection = dir; }
	Pos GetPos() { return this->pos; }
	void SetPos(Pos pos) { this->pos = pos; }
	string GetName() { return this->name; }
};