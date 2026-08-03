#include "PickupManager.h"
#include <iostream>

void PickupManager::Initialize(int size)
{
	mPickups.Resize(size);
}

void PickupManager::AddItem(PickupType pickupType, const Vector3& pos)
{
	mPickups.PushBack(PickUp{ pickupType, pos });

	PickUp item = mPickups[mPickups.Size() - 1];

	mTree.AddItem(&item.mPosition.x, &item);
}

const PickUp* PickupManager::GetClosestPickup(const Vector3& pos)
{
	return (PickUp*)mTree.FindNearest(&pos.x);
}

void PickupManager::ObtainPickupsInRange(const Vector3& pos, float range, PickupType pickupType)
{
	Vector<const void*> pickups;

	float minRange = pos.x - range;
	float maxRange = pos.x + range;

	PickUp::FilterByType filter;

	filter.type = pickupType;

	mTree.FindInRange(pickups, &minRange, &maxRange, filter);

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