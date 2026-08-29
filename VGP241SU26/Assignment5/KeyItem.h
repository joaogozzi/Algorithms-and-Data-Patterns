#pragma once
#include <string>

class KeyItem
{
public:
	KeyItem(){}
	KeyItem(const std::string& name);

	void Add(int amount);
	void Consume(int amount);
	int GetCount() const;
	void Print();

private:
	std::string mName;
	int mCount;
};