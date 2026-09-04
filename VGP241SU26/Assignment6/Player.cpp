#include "Player.h"

Player::Player()
{
	mName = "Player";
	Initialize();
}

Player::Player(const std::string& name)
	: mName(name)
{
	Initialize();
}

void Player::Initialize()
{
	mStats[(int)Stats::Health] = 100;
	mStats[(int)Stats::Speed] = (rand() % 81) + 20;
	mStats[(int)Stats::Attack] = (rand() % 16) + 5;
	mStats[(int)Stats::AttackCount] = 1;
}

int Player::GetStat(Stats stat) const
{
	return mStats[(int)stat];
}

void Player::SetStat(Stats stat, int value)
{
	mStats[(int)stat] = value;
}

bool Player::IsAlive() const
{
	return mStats[(int)Stats::Health] > 0;
}

std::string Player::GetName() const
{
	return mName;
}
