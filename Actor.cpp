#include "Actor.h"

Pos Actor::GetDirectionByPos()
{
	switch (this->moveDirection)
	{
	case DIRECTION::UP:
		return Pos(0, -1);
	case DIRECTION::DOWN:
		return Pos(0, 1);
	case DIRECTION::LEFT:
		return Pos(-1, 0);
	case DIRECTION::RIGHT:
		return Pos(1, 0);
	}
	return Pos();
}

Pos Actor::ActorKnockBack(Pos pos)
{
	if (pos == Pos(0, 0))
	{
		Pos KnockBackPos;
		switch (this->moveDirection)
		{
		case DIRECTION::UP:
			KnockBackPos = Pos(0, 1);
			break;
		case DIRECTION::DOWN:
			KnockBackPos = Pos(0, -1);
			break;
		case DIRECTION::LEFT:
			KnockBackPos = Pos(1, 0);
			break;
		case DIRECTION::RIGHT:
			KnockBackPos = Pos(-1, 0);
			break;
		}
		this->pos = this->pos + KnockBackPos;
	}
	else
	{
		this->pos = this->pos + pos;
	}
	return this->pos;
}
