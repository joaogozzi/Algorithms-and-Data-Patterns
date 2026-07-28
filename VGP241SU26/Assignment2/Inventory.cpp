#include "Inventory.h"
#include <PriorityQueue.h>

struct CompareValue
{
	bool operator()(Item* a, Item* b)
	{
		return a->GetValue() < b->GetValue();
	}
};

void Inventory::Initialize(int count)
{
	ItemType type = ItemType::COUNT;
	int value = 0;

	for (int i = 0; i < count; i++)
	{
		type = static_cast<ItemType>(rand() % static_cast<int>(ItemType::COUNT));
		value = rand() % 201 - 100;

		mItems.PushBack(Item(type, value));
	}
}

void Inventory::AddItem(ItemType itemType)
{
	for (int i = 0; i < mItems.Size(); i++)
	{
		if (mItems[i].GetType() == itemType)
		{
			mItems[i].AddItem();
			return;
		}
	}
}

void Inventory::DisplayInventory()
{
	PriorityQueue<Item*, CompareValue> queue;

	for (int i = 0; i < mItems.Size(); i++)
	{
		queue.Push(&mItems[i]);
	}

	while (!queue.Empty())
	{
		queue.Top()->DisplayItem();
		queue.Pop();
	}
}