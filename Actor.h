#pragma once
#include <string>

#include "Type.h"
using namespace std;

class Actor
{
	string name;
	Pos pos;
	int hp;
public:
	Actor(string Name, Pos pos, int hp)
	{
		this->name = Name;
		this->pos = pos;
		this->hp = hp;
	}
	Actor()
	{
		name = "";
		pos = Pos();
		hp = 0;
	}
	Pos GetPos() { return this->pos; }
	void SetPos(Pos pos) { this->pos = pos; }
	string GetName() { return this->name; }
};