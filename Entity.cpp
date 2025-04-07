#include "Entity.h"

string Entity::GetName() const
{
	return name;
}

Pos Entity::GetPos() const
{
	return pos;
}

EEntityType Entity::GetType() const
{
	return type;
}

void Entity::SetPos(const Pos& newPos)
{
	this->pos = newPos;
}
