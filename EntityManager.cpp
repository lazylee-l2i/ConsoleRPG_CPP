#include "EntityManager.h"

// DEBUG
#include <iostream>
#include <cassert>

void EntityManager::CreateEntity(EEntityType type, const Pos& pos, const int _opt)
{
	switch (type)
	{
	case EEntityType::PLAYER:
		{
			shared_ptr<Player> player = make_shared<Player>(pos);
			ActiveEntities.push_back(player);
			break;
		}
	case EEntityType::MONSTER:
		{
			shared_ptr<Monster> monster = make_shared<Monster>(monsterIndex);
			ActiveEntities.push_back(monster);
			monsterIndex += 1;
			break;
		}
	case EEntityType::ITEM:
		{
			shared_ptr<Item> item = CreateRandomItem(pos, _opt);
			if (item != nullptr) // Nullptr이면 확률에 의해 아이템 생성이 안된거
				ActiveEntities.push_back(item);
			break;
		}
	// WIP
	case EEntityType::NPC:
		{
			break;
		}
	// WIP
	case EEntityType::UNDEFINE:
		{
			break;
		}
	}
}

shared_ptr<Item> EntityManager::CreateRandomItem(const Pos& pos, const int _opt)
{
	shared_ptr<Item> item = nullptr;
	if (_opt == 0)
	{ 
		int random = rand() % 80;
		if (random < 50)
		{
			item = make_shared<Heart>(pos);
		}
		else if (random >= 50 && random < 70)
		{
			item = make_shared<Quest>(pos);
		}
		else if (random >= 70 && random < 80)
		{
			item = make_shared<MaxHeart>(pos);
		}
	}
	else
	{
		switch (_opt)
		{
		case 1:
			item = make_shared<Heart>(pos);
			break;
		case 2:
			item = make_shared<Quest>(pos);
			break;
		case 3:
			item = make_shared<MaxHeart>(pos);
			break;
		}
	}
	return item;
}

void EntityManager::RemoveEntityByName(const string& name)
{
	for (auto iter = ActiveEntities.begin(); iter != ActiveEntities.end();)
	{
		if (iter->get()->GetName() == name)
		{
			iter = ActiveEntities.erase(iter);
			return;
		}
		else
		{
			++iter;
		}
	}
}

void EntityManager::RemoveAllByType(EEntityType type)
{
	for (auto iter = ActiveEntities.begin(); iter != ActiveEntities.end();)
	{
		if (iter->get()->GetType() == type)
		{
			iter = ActiveEntities.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void EntityManager::RemoveByPos(Pos pos)
{
	for (auto iter = ActiveEntities.begin(); iter != ActiveEntities.end();)
	{
		if (iter->get()->GetPos() == pos)
		{
			iter = ActiveEntities.erase(iter);
			return;
		}
		else
		{
			++iter;
		}
	}
}

EInputType EntityManager::GetPlayerDirecion()
{
	for (const auto entity : ActiveEntities)
	{
		if (entity->GetType() == EEntityType::PLAYER)
		{
			Player* player = static_cast<Player*>(entity.get());
			return player->GetDirection();
		}
	}
	return EInputType::UNDEFINE;
}

shared_ptr<Player> EntityManager::GetPlayer()
{
	for (const auto entity : ActiveEntities)
	{
		if (entity->GetType() == EEntityType::PLAYER)
		{
			return dynamic_pointer_cast<Player>(entity);
		}
	}
	return nullptr;
}

vector<shared_ptr<Entity>>& EntityManager::GetAllEntities()
{
	return this->ActiveEntities;
}

shared_ptr<Entity> EntityManager::FindEntityByName(const string& name)
{
	for (const auto& entity : ActiveEntities)
	{
		if (entity->GetName() == name)
		{
			return entity;
		}
	}
	return nullptr;
}

shared_ptr<Entity> EntityManager::FindEntityByPos(const Pos& pos)
{
	for (const auto& entity : ActiveEntities)
	{
		if (entity->GetPos() == pos)
		{
			return entity;
		}
	}
	return nullptr;
}
