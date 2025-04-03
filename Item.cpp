#include "Item.h"

Item::Item(int i, Pos deadPoint)
{
	if(i == 1)
	{ 
		this->name = "heart";
		this->iEffectValue = 3;
		this->iStackSize = 0;
		this->iStackCount = 0;
		this->itemPos = deadPoint;
	}
	else if (i == 2)
	{
		this->name = "quest";
		this->iEffectValue = 1;
		this->iStackSize = 10;
		this->iStackCount = 0;
		this->itemPos = deadPoint;
	}
}

