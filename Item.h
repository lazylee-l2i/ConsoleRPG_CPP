#pragma once
#include <string>
#include <utility>
using namespace std;

class Actor;

class Item
{
private:
	string sName;
	char icon;
	int iEffectValue;
public:
	void TakeEffect(Actor& actor);
};