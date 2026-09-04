#include <iostream>
#include "Team.h"
#include <time.h>

int main()
{
	srand(time(0));

	Team teamA("Team Blue");
	Team teamB("Team Red");

	teamA.Initialize(20);
	teamB.Initialize(20);

	int turn = 1;

	while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
	{
		std::cout << "\n========== " << "TURN " << turn << " ==========\n";

		teamA.StartTurn();
		teamB.StartTurn();

		while (true)
		{
			Player* playerA = teamA.GetNextBattlingPlayer();
			Player* playerB = teamB.GetNextBattlingPlayer();

			if (playerA != nullptr && playerB != nullptr)
			{
				if (playerA->GetStat(Stats::Speed) >= playerB->GetStat(Stats::Speed))
					teamB.DamagePlayer(playerA);
				else
					teamA.DamagePlayer(playerB);
			}
			else if (playerA != nullptr)
			{
				teamB.DamagePlayer(playerA);
			}
			else if (playerB != nullptr)
			{
				teamA.DamagePlayer(playerB);
			}
			else
			{
				break;
			}

			teamA.OrderPlayers();
			teamB.OrderPlayers();

			if (teamA.GetRemainingPlayers() == 0 || teamB.GetRemainingPlayers() == 0)
				break;
		}

		std::cout << "\n";
		std::cout << teamA.GetName() << " remaining players: " << teamA.GetRemainingPlayers() << "\n";
		std::cout << teamB.GetName() << " remaining players: " << teamB.GetRemainingPlayers() << "\n";

		turn++;
	}

	std::cout << "\n========== FIGHT OVER ==========\n";

	if (teamA.GetRemainingPlayers() > 0)
		std::cout << teamA.GetName() << " WINS!\n";
	else
		std::cout << teamB.GetName() << " WINS!\n";

	return 0;
}