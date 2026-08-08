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

		pos.x = (float)(rand() % 501);
		pos.y = (float)(rand() % 501);
		pos.z = (float)(rand() % 501);

		manager.AddItem(type, pos);
	}

	manager.BuildTree();

	Vector3 player = { 250, 250, 250 };

	std::cout << "Pickups within 10 units\n";
	manager.ObtainPickupsInRange(player, 10.0f, PickupType::Invalid);

	std::cout << "\nHealth pickups within 50 units\n";
	manager.ObtainPickupsInRange(player, 50.0f, PickupType::Health);

	manager.Terminate();

	return 0;
}