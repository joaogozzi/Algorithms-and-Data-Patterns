#include "PickupManager.h"
#include <iostream>

void PickupManager::Initialize(int size)
{
	mPickups.Reserve(size);
}

void PickupManager::AddItem(PickupType pickupType, const Vector3& pos)
{
	mPickups.PushBack(PickUp{ pickupType, pos });

	mTree.AddItem(&mPickups[mPickups.Size() - 1].mPosition.x, &mPickups[mPickups.Size() - 1]);
}

const PickUp* PickupManager::GetClosestPickup(const Vector3& pos)
{
	return (PickUp*)mTree.FindNearest(&pos.x);
}

void PickupManager::ObtainPickupsInRangeByInvalid(const Vector3& pos, Vector3 range)
{
	Vector<const void*> pickups;

	Vector3 minRange = pos - range;
	Vector3 maxRange = pos + range;

	PickUp::FilterByInvalid	 filter;

	mTree.FindInRange(pickups, &minRange.x, &maxRange.x, filter);

	std::cout << "Size: " << pickups.Size() << "\n";

	for (Vector<const void*>::Iterator iter = pickups.Begin(); iter != pickups.End(); ++iter)
	{
		const PickUp* pickup = (const PickUp*)(*iter);

		std::cout << pickup->mName << " (" << pickup->mPosition.x << ", " << pickup->mPosition.y << ", " << pickup->mPosition.z << ")\n";
	}
}

void PickupManager::ObtainPickupsInRangeByHealth(const Vector3& pos, Vector3 range)
{
	Vector<const void*> pickups;

	Vector3 minRange = pos - range;
	Vector3 maxRange = pos + range;

	PickUp::FilterByHealth filter;

	mTree.FindInRange(pickups, &minRange.x, &maxRange.x, filter);

	std::cout << "Size: " << pickups.Size() << "\n";

	for (Vector<const void*>::Iterator iter = pickups.Begin(); iter != pickups.End(); ++iter)
	{
		const PickUp* pickup = (const PickUp*)(*iter);

		std::cout << pickup->mName << " (" << pickup->mPosition.x << ", " << pickup->mPosition.y << ", " << pickup->mPosition.z << ")\n";
	}
}

void PickupManager::BuildTree()
{
	mTree.BuildTree();
}

void PickupManager::Terminate()
{
	mTree.Terminate();
}