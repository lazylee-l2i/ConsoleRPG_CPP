#pragma once

struct Pos
{
	int x = 0;
	int y = 0;
	Pos() {}
	Pos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void operator=(const Pos& other)
	{
		this->x = other.x;
		this->y = other.y;
	}
};

Pos operator+(const Pos& left, const Pos& right)
{
	Pos _p;
	_p.x = left.x + right.x;
	_p.y = left.y + right.y;

	return _p;
}