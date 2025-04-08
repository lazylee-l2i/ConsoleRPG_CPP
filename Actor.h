#pragma once
#include <string>


#include "Entity.h"
#include "Type.h"

#include "EntityManager.h"
using namespace std;

class Entity;

class Actor : public Entity
{
protected:
	int ActorHP = 0;
	int MaxHP = 0;
	int ActorAttack = 0;
	Pos PostPos;
	EInputType inputType = EInputType::QUIT;
public:
	Actor() {}
	Actor(const string name, const Pos& pos) : Entity(name, pos) {}

	virtual ~Actor() {}

public:
	// Getter
	const EInputType GetDirection() { return this->inputType; }
	const Pos GetPos() { return this->pos; }
	const Pos GetPostPos() { return this->PostPos; }
	const string GetName() { return this->name; }
	const int GetHP() { return this->ActorHP; }
	const int GetAttack() { return this->ActorAttack; }
	const int GetMaxHP() { return this->MaxHP; }
	const Pos GetDirectionByPos();

	// Setter
	void SetDirection(EInputType dir) { this->inputType = dir; }
	void SetPos(Pos pos)
	{ 
		this->PostPos = this->pos;
		this->pos = pos;
	}
	void SetHP(int ActorHP) { this->ActorHP = ActorHP; }
	void SetAttack(int ActorAttack) { this->ActorAttack = ActorAttack; }

public:
	// Actor Unique Method
	Pos ActorKnockBack(Pos pos = Pos(0, 0));
	void ActorRollBack();
	
	// Method override by Entity
	virtual void Update() override;
	virtual void Interact(Entity* other) override;

	// Abstract Method at Actor
	virtual void Move() = 0;
	
};

class Player : public Actor
{
private:
	int QuestCount = 0;
	Pos AttackPos;
public:
	Player(const Pos& pos) : Actor("Player", pos) {
		this->name = "Player";
		this->ActorAttack = 5;
		this->ActorHP = 5;
		this->MaxHP = 10;
		this->pos = pos;
		this->PostPos = Pos(0, 0);
		this->type = EEntityType::PLAYER;
		this->inputType = EInputType::UNDEFINE;
	}
	virtual ~Player() {}
public:
	// Method override by Entity
	virtual void Update() override;
	virtual void Interact(Entity* other) override;

	// Abstract Method at Actor
	virtual void Move() override;

	// Unique Method
	void Attack(Entity* other);
	void SetAttackPos(EInputType dir);
	void SetMaxHP(int n) { this->MaxHP = n; }
	void EarnQuestItem() { this->QuestCount += 1; }

	Pos GetAttackPos();
	int GetMaxHP() { return this->MaxHP; }
	int GetQuestCount() { return this->QuestCount; }
};

class Monster : public Actor
{
public:
	Monster() {}
	Monster(int idx);
	virtual ~Monster() {}
public:
	// Method override by Entity
	virtual void Update() override;
	virtual void Interact(Entity* other) override;

	// Abstract Method at Actor
	virtual void Move() override;
};

class NPC : public Actor
{
private:

public:
	virtual ~NPC() {}
public:
	// Method override by Entity
	virtual void Update() override {};
	virtual void Interact(Entity* other) override {};

	// Abstract Method at Actor
	virtual void Move() override {};
};