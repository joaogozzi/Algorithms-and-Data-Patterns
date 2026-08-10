#pragma once
#include <string>
#include <KDTree.h>
#include <Vector3.h>

enum PickupType
{
	Invalid,
	Health,
	WeaponAmmo,
	Coins,
	Upgrade,
	SpecialItem,
	COUNT,
};

class PickUp
{
public:
	struct FilterByInvalid
	{
		bool operator()(const void* data)
		{
			const PickUp* item = (const PickUp*)data;
			return item->mType == PickupType::Invalid;
		}
	};

	struct FilterByHealth
	{
		bool operator()(const void* data)
		{
			const PickUp* item = (const PickUp*)data;
			return item->mType == PickupType::Health;
		}
	};

	PickUp() {}
	PickUp(PickupType pickupType, const Vector3& pos);

	std::string mName;
	PickupType mType;
	Vector3 mPosition;

private:
	
};