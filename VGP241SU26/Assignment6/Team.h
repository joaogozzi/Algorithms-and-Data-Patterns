#pragma once
#include <string>
#include <Vector.h>
#include "Player.h"

struct CompareSpeed
{
	bool operator()(Player& a, Player& b) const
	{
		if (a.GetStat(Stats::AttackCount) > 0)
			return a.GetStat(Stats::Speed) > b.GetStat(Stats::Speed);
		else
			return false;
	};
};

class Team
{
public:
	Team(const std::string& name);

	void Initialize(int numPlayers);
	Player* GetNextBattlingPlayer();
	void DamagePlayer(Player* player);
	int GetRemainingPlayers();
	void OrderPlayers();
	void StartTurn();
	std::string GetName() const;

private:
	std::string mName;
	Vector<Player> mPlayers;
};