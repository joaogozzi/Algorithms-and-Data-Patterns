#include <iostream>
#include <UnorderedMap.h>
#include <Vector.h>
#include <Global.h>

#include "Entity.h"

int main()
{
	Vector<Entity> myEntities;

	Entity player1;
	player1.Initialize("Player_Texture_01");

	Entity player2;
	player2.Initialize("Player_Texture_02");

	myEntities.PushBack(player1);
	myEntities.PushBack(player2);

	for (int i = 0; i < 20; ++i)
	{
		Entity enemy;

		enemy.Initialize("Enemy_Texture");

		myEntities.PushBack(enemy);
	}

	for (int iteration = 0; iteration < 4; ++iteration)
	{
		std::cout << "\n========== ITERATION " << iteration + 1 << " ==========\n" << "\n";

		for (std::size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Update();
		}

		Global::BubbleSort(myEntities, [](const Entity& a, const Entity& b)
			{
				return a.GetDistanceFromOrigin() < b.GetDistanceFromOrigin();
			}
		);

		for (std::size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Render();
		}
	}
}