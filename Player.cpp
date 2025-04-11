#include "Actor.h"
#include "Item.h"
#include "InputManager.h"
#include "GameManager.h"

void Player::Update()
{
	Move();
}

void Player::Interact(Entity* other)
{
	EEntityType type = other->GetType();
	if (type == EEntityType::MONSTER)
	{
		this->ActorKnockBack();
		this->ActorHP -= 1;
		this->SetOnHit(true);
		if (this->ActorHP == 0)
		{
			GET_SINGLE(GameManager).ChangeGameLoopFlag();
		}
	}
}

void Player::Move()
{
	this->PostPos = this->pos;
	EInputType DirCommand = GET_SINGLE(InputManager).PlayerInput();
	switch (DirCommand)
	{
	case EInputType::UP:
		this->pos.y--;
		this->SetDirection(DirCommand);
		break;
	case EInputType::DOWN:
		this->SetDirection(DirCommand);
		this->pos.y++;
		break;
	case EInputType::LEFT:
		this->SetDirection(DirCommand);
		this->pos.x--;
		break;
	case EInputType::RIGHT:
		this->SetDirection(DirCommand);
		this->pos.x++;
		break;
	case EInputType::ATTACKCALL:
		this->SetAttackPos(DirCommand);
		break;
	case EInputType::QUIT:
		GET_SINGLE(GameManager).ChangeGameLoopFlag();
		break;
	case EInputType::COMMAND_MODE:
		GET_SINGLE(GameManager).ChangeCommandFlag();
	}
	
}

void Player::SetAttackPos(EInputType dir)
{
	switch (this->GetDirection())
	{
	case EInputType::UP:
		this->AttackPos = this->pos + Pos(0, -1);
		break;
	case EInputType::DOWN:
		this->AttackPos = this->pos + Pos(0, 1);
		break;
	case EInputType::LEFT:
		this->AttackPos = this->pos + Pos(-1, 0);
		break;
	case EInputType::RIGHT:
		this->AttackPos = this->pos + Pos(1, 0);
		break;
	}
}

void Player::Attack(Entity* other)
{
	if (Monster* monster = static_cast<Monster*>(other))
	{
		Pos spawnPoint = monster->GetPos();
		monster->ActorKnockBack(this->GetDirectionByPos());
		int remainHP = monster->GetHP() - this->ActorAttack;
		if (remainHP <= 0)
		{
			GET_SINGLE(EntityManager).RemoveEntityByName(other->GetName());
			GET_SINGLE(EntityManager).CreateEntity(EEntityType::ITEM, spawnPoint);
		}
		else
		{
			monster->SetHP(remainHP);
		}
		
	}
}



Pos Player::GetAttackPos()
{
	return this->AttackPos;
}

string Player::ShowPlayerStatus()
{
	string status = "";

	status += "HP    : ";
	for (int i = 0; i < this->ActorHP; i++)
	{
		status += "¢¾ ";
	}

	for (int i = 0; i < this->MaxHP - this->ActorHP; i++)
	{
		status += "¢½ ";
	}
	status += "\n";


	status += "Quest : ";
	for (int i = 0; i < this->QuestCount; i++)
	{
		status += "¢Ý ";
	}
	status += "\n";

	return status;
}

