#pragma once

struct Pos
{
	int x = 0;
	int y = 0;
	Pos() {}
	Pos(int x, int y);

	//void operator=(const Pos& other);
};

Pos operator+(const Pos& left, const Pos& right);

Pos operator-(const Pos& left, const Pos& right);

bool operator==(const Pos& left, const Pos& right);

int GetLengthAboutTwoPoint(const Pos& left, const Pos& right);

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	QUIT,
	ATTACKCALL
};