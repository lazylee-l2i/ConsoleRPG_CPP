#include "Type.h"

Pos operator+(const Pos& left, const Pos& right)
{
	Pos _p;
	_p.x = left.x + right.x;
	_p.y = left.y + right.y;

	return _p;
}

Pos operator-(const Pos& left, const Pos& right)
{
	Pos _p;
	_p.x = left.x - right.x;
	_p.y = left.y - right.y;

	return _p;
}

bool operator==(const Pos& left, const Pos& right)
{
	bool bX = left.x == right.x;
	bool bY = left.y == right.y;

	return bX && bY;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Pos::operator=(const Pos& other)
{
	this->x = other.x;
	this->y = other.y;
}

