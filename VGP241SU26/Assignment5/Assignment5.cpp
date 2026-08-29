#include <iostream>
#include "Inventory.h"
#include <time.h>

void ClearConsole()
{
	std::system("cls");
}

void WaitForEnter()
{
	std::cout << "\n" << "Press ENTER to continue" << "\n";

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

int main()
{
	srand(time(0));

	Inventory& inventory = Inventory::GetInstance();

	Vector<std::string> mKeyNames;

	mKeyNames.PushBack("Red Key");
	mKeyNames.PushBack("Blue Key");
	mKeyNames.PushBack("Green Key");
	mKeyNames.PushBack("Yellow Key");
	mKeyNames.PushBack("Purple Key");
	mKeyNames.PushBack("Orange Key");
	mKeyNames.PushBack("Silver Key");
	mKeyNames.PushBack("Gold Key");
	mKeyNames.PushBack("Iron Key");
	mKeyNames.PushBack("Bronze Key");
	mKeyNames.PushBack("Crystal Key");
	mKeyNames.PushBack("Ruby Key");
	mKeyNames.PushBack("Sapphire Key");
	mKeyNames.PushBack("Emerald Key");
	mKeyNames.PushBack("Diamond Key");
	mKeyNames.PushBack("Ancient Key");
	mKeyNames.PushBack("Magic Key");
	mKeyNames.PushBack("Dark Key");
	mKeyNames.PushBack("Light Key");
	mKeyNames.PushBack("Master Key");

	for (int i = 0; i < 100; ++i)
	{
		int randomIndex = rand() % mKeyNames.Size();
		inventory.PickupKey(mKeyNames[randomIndex], 1);
	}

	std::cout << "==================== INITIAL INVENTORY ====================\n";
	inventory.PrintKeys();

	WaitForEnter();

	int doorsAttempted = 0;
	int doorsUnlocked = 0;

	bool gameRunning = true;

	while (gameRunning)
	{
		//ClearConsole();

		std::cout << "\n==================== PLAYER ACTION ====================\n";
		std::cout << "1 - Open Door\n";
		std::cout << "2 - Pick Up Key\n";
		std::cout << "3 - Exit\n";
		std::cout << "Choose an option: ";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			++doorsAttempted;

			int randomIndex = rand() % mKeyNames.Size();
			std::string randomKey = mKeyNames[randomIndex];

			std::cout << "\nYou arrive at a door and need a " << randomKey << "\n";

			if (inventory.HasKey(randomKey))
			{
				std::cout << "You have the " << randomKey << " and have unlocked the door\n";

				inventory.UseKey(randomKey, 1);

				++doorsUnlocked;
			}
			else
			{
				std::cout << "You do not have the " << randomKey << ", the door will remain locked\n";
			}
			break;
		}
		case 2:
		{
			int randomIndex = rand() % mKeyNames.Size();
			std::string randomKey = mKeyNames[randomIndex];

			inventory.PickupKey(randomKey, 1);

			std::cout << "\nYou picked up a " << randomKey << "\n";

			std::cout << "You now have " << inventory.GetKeyCount(randomKey) << " " << randomKey << "(s)\n";
			break;
		}
		case 3:
		{
			gameRunning = false;
			break;
		}
		default:
		{
			std::cout << "Invalid option.\n";
			break;
		}
		}

		WaitForEnter();
	}

	system("cls");

	std::cout << "\n==================== GAMEOVER ====================\n";

	inventory.PrintKeys();

	std::cout << "\nTotal doors unlocked: " << doorsUnlocked << "\n";
	std::cout << "Doors attempted without the key: " << doorsAttempted - doorsUnlocked << "\n";

	return 0;
}
