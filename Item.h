#pragma once
#include <string>

#include "Entity.h"
#include "Actor.h"
#include "Type.h"
using namespace std;

class Entity;

class Item : public Entity
{
	EItemType ItemType = EItemType::UNDEFINE;
	int ItemEffectValue = 0;
	int ItemStackSize = 0;
	int ItemCount = 0;
public:
	Item() {}
	Item(EItemType type, Pos SpawnPoint);
	virtual ~Item() {}

	int GetItemCount() { return this->ItemCount; }
	int GetItemStackSize() { return this->ItemStackSize; }
	EItemType GetItemType() { return this->ItemType; }

	void PlusItemCount() { this->ItemCount += 1; }

	virtual void Update() override;
	virtual void Interact(Entity* other) override;
};