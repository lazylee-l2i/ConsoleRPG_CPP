#include "Actor.h"

const Pos Actor::GetDirectionByPos()
{
	switch (this->inputType)
	{
	case EInputType::UP:
		return Pos(0, -1);
	case EInputType::DOWN:
		return Pos(0, 1);
	case EInputType::LEFT:
		return Pos(-1, 0);
	case EInputType::RIGHT:
		return Pos(1, 0);
	}
	return Pos();
}

void Actor::Update()
{
}

void Actor::Interact(Entity* other)
{

}

Pos Actor::ActorKnockBack(Pos pos)
{
	this->pos = this->pos - this->GetDirectionByPos() - this->GetDirectionByPos();
	return this->pos;
}

void Actor::ActorRollBack()
{
	this->pos = this->pos - this->GetDirectionByPos();
}


