#pragma once
#include <Vector.h>
#include "Item.h"

class Inventory
{
public:
	void Initialize(int count);
	void AddItem(ItemType itemType);
	void DisplayInventory();

private:
	Vector<Item> mItems;
};