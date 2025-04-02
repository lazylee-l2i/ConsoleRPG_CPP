#include "Type.h"
#include <math.h>

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

int GetLengthAboutTwoPoint(const Pos& left, const Pos& right)
{
	int x = pow(right.x - left.x, 2);
	int y = pow(right.y - left.y, 2);
	int result = x + y;
	// 이 메소드는 그냥 두 점 사이의 거리가 1일때가 중요해서
	// sqrt는 굳이 안넣음.
	// result = sqrt(result);
	return result;
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

