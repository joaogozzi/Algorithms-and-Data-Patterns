#include <iostream>
#include "PickupManager.h"

int main()
{
	PickupManager manager;

	manager.Initialize(100);

	for (int i = 0; i < 100; i++)
	{
		PickupType type = (PickupType)(rand() % (int)PickupType::COUNT);

		Vector3 pos;

		pos.x = (float)(rand() % 101);
		pos.y = (float)(rand() % 21);
		pos.z = (float)(rand() % 101);

		manager.AddItem(type, pos);
	}

	manager.BuildTree();

	Vector3 player = { 50, 25, 50 };

	std::cout << "Invalid pickups within 10 units\n";
	manager.ObtainPickupsInRangeByInvalid(player, Vector3{ 10.0f, 10.0f, 10.0f });

	std::cout << "\nHealth pickups within 50 units\n";
	manager.ObtainPickupsInRangeByHealth(player, Vector3{ 50.0f, 50.0f, 50.0f });

	manager.Terminate();

	return 0;
}