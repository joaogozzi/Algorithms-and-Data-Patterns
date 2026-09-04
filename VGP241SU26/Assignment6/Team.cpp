#include "Team.h"
#include <Global.h>
#include <iostream>

Team::Team(const std::string& name)
	:mName(name)
{
}

void Team::Initialize(int numPlayers)
{
	mPlayers.Clear();

	for (int i = 0; i < numPlayers; ++i)
	{
		std::string playerName = mName + " Player " + std::to_string(i + 1);
		mPlayers.PushBack(playerName);
	}

	OrderPlayers();
}

Player* Team::GetNextBattlingPlayer()
{
	for (int i = 0; i < mPlayers.Size(); ++i)
	{
		if (mPlayers[i].IsAlive() && mPlayers[i].GetStat(Stats::AttackCount) > 0)
			return &mPlayers[i];
	}

	return nullptr;
}

void Team::DamagePlayer(Player* player)
{
	if (player == nullptr)
		return;

	Vector<Player*> livingPlayers;

	for (int i = 0; i < mPlayers.Size(); ++i)
	{
		if (mPlayers[i].IsAlive())
			livingPlayers.PushBack(&mPlayers[i]);
	}

	if (livingPlayers.Size() == 0)
		return;

	int randomIndex = rand() % livingPlayers.Size();

	Player* target = livingPlayers[randomIndex];

	int damage = player->GetStat(Stats::Attack);
	int oldHealth = target->GetStat(Stats::Health);
	int newHealth = oldHealth - damage;

	if (newHealth < 0)
		newHealth = 0;

	target->SetStat(Stats::Health, newHealth);

	std::cout << player->GetName() << " dealt " << damage << " of damage " << " to " << target->GetName() << "!\n";
	std::cout << target->GetName() << " HP: " << newHealth << "\n";

	if (target->IsAlive() && rand() % 100 < 25)
	{
		int speed = target->GetStat(Stats::Speed);

		speed -= 10;

		if (speed < 5)
			speed = 5;

		target->SetStat(Stats::Speed, speed);

		std::cout << target->GetName() << " was slowed! Speed: " << speed << "\n";
	}

	if (rand() % 100 < 10)
	{
		int speed = player->GetStat(Stats::Speed);

		speed += 5;

		player->SetStat(Stats::Speed, speed);

		std::cout << player->GetName() << " sped up! Speed: " << speed << "\n";
	}

	player->SetStat(Stats::AttackCount, 0);
}

int Team::GetRemainingPlayers()
{
	int remainPlayers = 0;

	for (int i = 0; i < mPlayers.Size(); ++i)
	{
		if (mPlayers[i].IsAlive())
			remainPlayers++;
	}

	return remainPlayers;
}

void Team::OrderPlayers()
{
	Global::IntroSort(mPlayers.Begin(), mPlayers.End(), CompareSpeed());
}

void Team::StartTurn()
{
	for (int i = 0; i < mPlayers.Size(); ++i)
	{
		mPlayers[i].SetStat(Stats::AttackCount, 1);
	}

	OrderPlayers();
}

std::string Team::GetName() const
{
	return mName;
}