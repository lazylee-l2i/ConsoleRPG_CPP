#include "Actor.h"
#include "InputManager.h"
#include "MapManager.h"
#include "GameManager.h"

Monster::Monster(int idx)
{
	this->name = "M" + to_string(idx);
	this->ActorAttack = 1;
	this->ActorHP = 5;
	this->MaxHP = 0;
	Pos tempPos = GET_SINGLE(InputManager).GetRandomPos();
	while (true)
	{
		if (GET_SINGLE(MapManager).GetTile(tempPos.x, tempPos.y) == EMapTileType::WALL)
		{
			tempPos = GET_SINGLE(InputManager).GetRandomPos();
		}
		else if(GET_SINGLE(MapManager).GetTile(tempPos.x, tempPos.y) == EMapTileType::EXIT)
		{
			tempPos = GET_SINGLE(InputManager).GetRandomPos();
		}
		else
		{
			break;
		}
	}

	this->pos = tempPos;
	this->PostPos = Pos();
	this->type = EEntityType::MONSTER;
	this->inputType = EInputType::UNDEFINE;
}

void Monster::Update()
{
	Move();
}

void Monster::Interact(Entity* other)
{
	EEntityType type = other->GetType();
	if (type == EEntityType::PLAYER)
	{
		Player* player = static_cast<Player*>(other);
		//player->ActorRollBack();
		Pos knockBackPos = player->GetPos() + this->GetDirectionByPos();
		EMapTileType type = GET_SINGLE(MapManager).GetTile(knockBackPos.x, knockBackPos.y);
		player->SetOnHit(true);


		int remainHP = player->GetHP() - this->ActorAttack;
		remainHP = remainHP <= 0 ? 0 : remainHP;
		player->SetHP(remainHP);
		if (remainHP <= 0)
		{
			player->SetAlive(false);
		}
		if (type != EMapTileType::WALL && type != EMapTileType::EXIT)
		{
			player->SetPos(knockBackPos);
		}

	}
}

void Monster::Move()
{
	this->PostPos = this->pos;
	EInputType input = GET_SINGLE(InputManager).MonsterInput();
	this->SetDirection(input);
	switch (input)
	{
	case EInputType::UP:
		this->pos.y--;
		break;
	case EInputType::DOWN:
		this->pos.y++;
		break;
	case EInputType::LEFT:
		this->pos.x--;
		break;
	case EInputType::RIGHT:
		this->pos.x++;
		break;
	}
}