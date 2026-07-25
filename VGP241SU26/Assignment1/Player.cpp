#include "Player.h"
#include <iostream>

Player::Player()
{
	mName = "Cleiton";

	mStats[Stats::Health] = 100;

	for (int i = Attack; i < Stats::Count; i++)
	{
		mStats[i] = rand() % 5 + 1;
	}
}

Player::Player(const std::string& name)
	: mName(name)
{
	mStats[Stats::Health] = 100;

	for (int i = Attack; i < Stats::Count; i++)
	{
		mStats[i] = rand() % 5 + 1;
	}
}

void Player::DisplayInfo() const
{
	std::cout << "========================================\n";
	std::cout << "Name: " << mName << "\n";
	std::cout << "Health: " << mStats[Stats::Health] << "\n";
	std::cout << "Attack: " << mStats[Stats::Attack] << "\n";
	std::cout << "Defense: " << mStats[Stats::Defense] << "\n";
	std::cout << "Stamina: " << mStats[Stats::Stamina] << "\n";
	std::cout << "Speed: " << mStats[Stats::Speed] << "\n";
	std::cout << "========================================\n";
}

int Player::GetStats(Stats stats) const
{
	return mStats[stats];
}

std::string Player::GetName() const
{
	return mName;
}
