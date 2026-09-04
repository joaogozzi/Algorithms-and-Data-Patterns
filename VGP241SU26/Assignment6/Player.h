#pragma once
#include <string>
#include <Array.h>

enum class Stats
{
	Health,
	Attack,
	Speed,
	AttackCount
};

class Player
{
public:
	Player();
	Player(const std::string& name);

	void Initialize();
	int GetStat(Stats stat) const;
	void SetStat(Stats stat, int value);
	bool IsAlive() const;
	std::string GetName() const;

private:
	std::string mName;
	Array<int, 4> mStats;
};