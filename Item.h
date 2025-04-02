#pragma once
#include <string>
#include "Type.h"
using namespace std;

class Item
{
	string name = "";
	int iEffectValue = 0;
	int iStackSize = 0;
	int iStackCount = 0;
	Pos itemPos;
public:
	Item() {}
	Item(int i, Pos deadPoint);
	~Item() {}
	Pos GetItemPos() { return this->itemPos; }
	string GetItemName() { return this->name; }
	int GetItemEffectValue() { return this->iEffectValue; }
	int GetItemCount() { return this->iStackCount; }
	int GetItemStackSize() { return this->iStackSize; }

	void PlusItemCount() { this->iStackCount += 1; }
};