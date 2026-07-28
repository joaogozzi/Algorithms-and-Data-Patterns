#pragma once
#include <string>

enum ItemType
{
	SmallHealth,
	MedHealth,
	LightningSpell,
	Grenade,
	Sword,
	Bow,
	Chestplate,
	Leggings,
	Shield,
	Bomb,
	COUNT
};

class Item
{
public:
	Item();
	Item(ItemType type, int value);

	void ConsumeItem();
	void AddItem();

	void DisplayItem() const;

	std::string GetName() const;
	ItemType GetType() const;
	int GetValue() const;
	int GetCount() const;

private:
	std::string mName;
	ItemType mType;
	int mValue;
	int mCount;
};