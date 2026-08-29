#include "Inventory.h"

Inventory& Inventory::GetInstance()
{
	static Inventory instance;
	return instance;
}

void Inventory::PickupKey(const std::string& keyName, int amount)
{
	if (!mKeys.Has(keyName))
	{
		KeyItem newKey(keyName);
		mKeys.Insert(keyName, newKey);
	}

	mKeys[keyName].Add(amount);
}

void Inventory::UseKey(const std::string& keyName, int amount)
{
	if (!mKeys.Has(keyName))
	{
		return;
	}

	mKeys[keyName].Consume(amount);

	if (mKeys[keyName].GetCount() == 0)
	{
		mKeys.Remove(keyName);
	}
}

bool Inventory::HasKey(const std::string& keyName) const
{
	return mKeys.Has(keyName);
}

int Inventory::GetKeyCount(const std::string& keyName) const
{
	if (!mKeys.Has(keyName))
		return 0;

	return mKeys[keyName].GetCount();
}

void Inventory::PrintKeys()
{
	Vector<std::string> keys;
	mKeys.ObtainKeys(keys);

	for (int i = 0; i < keys.Size(); ++i)
	{
		mKeys[keys[i]].Print();
	}
}