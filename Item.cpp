#include "Item.h"

Item::Item(EItemType type, Pos SpawnPoint)
{
	switch (type)
	{
	case EItemType::HEART:
		this->ItemType = EItemType::HEART;
		break;
	case EItemType::QUEST:
		this->ItemType = EItemType::QUEST;
		break;
	case EItemType::UNDEFINE:
		this->ItemType = EItemType::UNDEFINE;
		break;
	}
	this->type = EEntityType::ITEM;
	this->pos = SpawnPoint;
}

void Item::Update()
{
	// Item is only updated by player interaction
}

void Item::Interact(Entity* other)
{
	if (other->GetType() == EEntityType::MONSTER)
		return;
}

