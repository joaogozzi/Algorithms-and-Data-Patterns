#pragma once
#include <Map.h>
#include "KeyItem.h"

class Inventory
{
public:
	Inventory() {}

	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	static Inventory& GetInstance();

	void PickupKey(const std::string& keyName, int amount);
	void UseKey(const std::string& keyName, int amount);

	bool HasKey(const std::string& keyName) const;

	int GetKeyCount(const std::string& keyName) const;

	void PrintKeys();

private:
	Map<std::string, KeyItem> mKeys;
};