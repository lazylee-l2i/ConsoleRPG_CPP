#pragma once

#include <string>
#include "Utill.h"
using namespace std;

class Entity
{
protected:
	string name;
	Pos pos;
	EEntityType type = EEntityType::UNDEFINE;

public:
	Entity() {}
	Entity(string name, const Pos& pos) : name(name), pos(pos) {}
	virtual ~Entity() {}

	virtual void Update() = 0;
	virtual void Interact(Entity* other) = 0;

	string GetName() const;
	Pos GetPos() const;
	EEntityType GetType() const;

	void SetPos(const Pos& newPos);
};