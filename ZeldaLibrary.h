#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <random>
#include <Windows.h>
using namespace std;

struct Pos {
	int x = 0;
	int y = 0;

	Pos() {}
	Pos(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}


	Pos operator+=(const Pos& object);
	Pos operator-=(const Pos& object);
	Pos operator+=(int _n);
	Pos operator-=(int _n);
	
	Pos operator+(Pos object);
	Pos operator-(Pos object);
	
	Pos operator=(Pos object);
	Pos operator=(int _n);

	bool operator==(Pos& object) const;
	bool operator!=(Pos& object) const;

	bool operator<(Pos& object) const;
	bool operator>(Pos& object) const;

	bool operator&&(Pos& object) const;
	bool operator||(Pos& object) const;

	string GetString();
	int Make1D();
};