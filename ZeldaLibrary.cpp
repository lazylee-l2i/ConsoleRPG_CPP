#include "ZeldaLibrary.h"


Pos Pos::operator+=(const Pos& object)
{
	this->x += object.x;
	this->y += object.y;
	return *this;
}

Pos Pos::operator+=(int _n)
{
	this->x += _n;
	this->y += _n;
	return *this;
}

Pos Pos::operator-=(const Pos& object)
{
	this->x -= object.x;
	this->y -= object.y;
	return *this;
}


Pos Pos::operator-=(int _n)
{
	this->x -= _n;
	this->y -= _n;
	return *this;
}

Pos Pos::operator+(Pos object)
{
	this->x += object.x;
	this->y += object.y;
	return *this;
}

Pos Pos::operator-(Pos object)
{
	this->x -= object.x;
	this->y -= object.y;
	return *this;
}

Pos Pos::operator=(Pos object)
{
	this->x = object.x;
	this->y = object.y;
	return *this;
}

Pos Pos::operator=(int _n)
{
	this->x = _n;
	this->y = _n;
	return *this;
}

bool Pos::operator==(Pos& object) const
{
	bool b1 = (this->x == object.x);
	bool b2 = (this->y == object.y);
	return b1 && b2;
}

bool Pos::operator!=(Pos& object) const
{
	bool b1 = (this->x != object.x);
	bool b2 = (this->y != object.y);

	// 둘다 같다 => b1과 b2가 참이다 => 그 외는 거짓 => AND 연산
	return b1 && b2;
}

bool Pos::operator<(Pos& object) const
{
	bool b1 = (this->x < object.x);
	bool b2 = (this->y < object.y);
	return b1 && b2;
}

bool Pos::operator>(Pos& object) const
{
	bool b1 = (this->x > object.x);
	bool b2 = (this->y > object.y);
	return b1 && b2;
}

bool Pos::operator&&(Pos& object) const
{
	bool b1 = (this->x && object.x);
	bool b2 = (this->y && object.y);
	return b1 && b2;
}

bool Pos::operator||(Pos& object) const
{
	bool b1 = (this->x || object.x);
	bool b2 = (this->y || object.y);
	return b1 || b2;
}

string Pos::GetString()
{
	string s = to_string(this->x) + " | " + to_string(this->y);
	return s;
}

int Pos::Make1D()
{
	return (this->x + (this->y * 10));
}
