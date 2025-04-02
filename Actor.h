#pragma once
#include <string>

#include "Type.h"
using namespace std;

class Actor
{
	string name;
	int hp;
	int attack = 0;
	Pos pos;
	DIRECTION moveDirection = DIRECTION::QUIT;
public:
	Actor(string Name, const Pos& pos, int hp)
	{
		this->name = Name;
		this->pos = pos;
		this->hp = hp;
		if (Name == "User")
		{ 
			this->attack = 5;
		}
		else
		{ 
			this->attack = 1;
		}
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

	// Getter
	DIRECTION GetDirection() { return this->moveDirection; }
	Pos GetDirectionByPos();
	Pos GetPos() { return this->pos; }
	string GetName() { return this->name; }
	int GetHP() { return this->hp; }
	int GetAttack() { return this->attack; }

	// Setter
	void SetDirection(DIRECTION dir) { this->moveDirection = dir; }
	void SetPos(Pos pos) { this->pos = pos; }
	void SetHP(int hp) { this->hp = hp; }
	void SetAttack(int attack) { this->attack = attack; }
	
	// Method
	void ActorKnockBack(Pos pos = Pos(0, 0));
};