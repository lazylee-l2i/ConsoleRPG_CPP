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

Heart::Heart(Pos SpawnPoint)
{
	this->type = EEntityType::ITEM;
	this->ItemType = EItemType::HEART;
	this->pos = SpawnPoint;
}

void Heart::Update()
{
}

void Heart::Interact(Entity* other)
{
	if (Player* player = dynamic_cast<Player*>(other))
	{
		int HP = player->GetHP() + 2;
		if (HP > player->GetMaxHP())
		{
			player->SetHP(player->GetMaxHP());
		}
		else
		{
			player->SetHP(HP);
		}
	}
	
}

Quest::Quest(Pos SpawnPoint)
{
	this->type = EEntityType::ITEM;
	this->ItemType = EItemType::QUEST;
	this->pos = SpawnPoint;
}

void Quest::Update()
{
}

void Quest::Interact(Entity* other)
{
	if (Player* player = dynamic_cast<Player*>(other))
	{
		player->EarnQuestItem();
	}
}

MaxHeart::MaxHeart(Pos SpawnPoint)
{
	this->type = EEntityType::ITEM;
	this->ItemType = EItemType::MAXHEART;
	this->pos = SpawnPoint;
}

void MaxHeart::Update()
{

}

void MaxHeart::Interact(Entity* other)
{
	if (Player* player = dynamic_cast<Player*>(other))
	{
		player->SetMaxHP(player->GetMaxHP() + 1);
	}
}
