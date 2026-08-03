#include "PickUp.h"

PickUp::PickUp(PickupType pickupType, const Vector3& pos)
	: mType(pickupType),
	mPosition(pos)
{
	std::string name;

	switch (pickupType)
	{
	case Invalid:
		name = "Invalid";
		break;
	case Health:
		name = "Health";
		break;
	case WeaponAmmo:
		name = "Weapon Ammo";
		break;
	case Coins:
		name = "Coins";
		break;
	case Upgrade:
		name = "Upgrade";
		break;
	case SpecialItem:
		name = "Special Item";
		break;
	default:
		name = "Item";
		break;
	}

	mName = name;
}