#include "KeyItem.h"
#include <iostream>

KeyItem::KeyItem(const std::string& name)
	: mName(name)
{
	mCount = 0;
}

void KeyItem::Add(int amount)
{
	if (amount > 0)
		mCount += amount;
}

void KeyItem::Consume(int amount)
{
	mCount -= amount;

	if (mCount < 0)
		mCount = 0;
}

int KeyItem::GetCount() const
{
	return mCount;
}

void KeyItem::Print()
{
	std::cout << mName << ": " << mCount << "\n";
}