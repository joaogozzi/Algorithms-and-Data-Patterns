#pragma once
#include <string>
#include <Array.h>

enum Stats
{
	Health,
	Attack,
	Defense,
	Stamina,
	Speed,
	Count,
};

class Player
{
public:
	Player();
	Player(const std::string& name);

	void DisplayInfo() const;

	int GetStats(Stats stats) const;
	std::string GetName() const;

private:
	std::string mName;
	Array<int, Stats::Count> mStats;
};