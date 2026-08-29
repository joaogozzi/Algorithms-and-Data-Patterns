#include "KeyItem.h"
#include "Item.h"
#include <iostream>

Item::Item()
	: mName("Default Item"),
	mType(ItemType::Sword),
	mValue(10),
	mCount(1)
{}

Item::Item(ItemType type, int value)
	: mType(type),
	mValue(value)
{
	switch (type)
	{
	case SmallHealth:
		mName = "SmallHealth";
		break;

	case MedHealth:
		mName = "MedHealth";
		break;

	case LightningSpell:
		mName = "LightningSpell";
		break;

	case Grenade:
		mName = "Grenade";
		break;

	case Sword:
		mName = "Sword";
		break;

	case Bow:
		mName = "Bow";
		break;

	case Chestplate:
		mName = "Chestplate";
		break;

	case Leggings:
		mName = "Leggings";
		break;

	case Shield:
		mName = "Shield";
		break;

	case Bomb:
		mName = "Bomb";
		break;
	}

	mCount = 0;
}

void Item::ConsumeItem()
{
	if (mCount > 0)
	{
		mCount--;
		std::cout << "Cosumed " << mName << " | " << "Value: " << mValue << "\n";
	}
	else
	{
		std::cout << "You don`t have any " << mName << " to consume" << "\n";
	}
}

void Item::AddItem()
{
	mCount++;
	std::cout << "Add " << mName << "\n";
}

void Item::DisplayItem() const
{
	std::cout << "\nItem infos\n";
	std::cout << "Name: " << mName << "\n";
	std::cout << "Type: " << mType << "\n";
	std::cout << "Value: " << mValue << "\n";
	std::cout << "Count: " << mCount << "\n";
}

std::string Item::GetName() const
{
	return mName;
}

ItemType Item::GetType() const
{
	return mType;
}

int Item::GetValue() const
{
	return mValue;
}

int Item::GetCount() const
{
	return mCount;
}