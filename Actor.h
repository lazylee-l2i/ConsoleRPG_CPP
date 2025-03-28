#pragma once
//#include <iostream>
#include <string>
#include <utility>
using namespace std;

struct Pos {
	int x = 0;
	int y = 0;
	Pos operator+=(Pos& object);
	Pos operator-=(Pos& object);

	bool operator==(Pos& object) const;
	bool operator!=(Pos& object) const;

	bool operator<(Pos& object) const;
	bool operator>(Pos& object) const;

	bool operator&&(Pos& object) const;
	bool operator||(Pos& object) const;
};

class Actor
{
protected:
	string sName;
	int iHP;
	char cIcon;
	Pos pActorPos;
	
public:
	Actor(string name);
	Actor(string name, int hp, Pos pos);
	virtual ~Actor();

	virtual void move() = 0;
	virtual void attack() = 0;
};

class Item;

class Player : public Actor
{
public:
	void GetItem(Item item);
	virtual void move() override;
	virtual void attack() override;
};

class Monster : public Actor
{
public:
	virtual void move() override;
	virtual void attack() override;
};

class NPC : public Actor
{
public:
	void TellToPlayer();
	virtual void move() override {};
	virtual void attack() override;
};