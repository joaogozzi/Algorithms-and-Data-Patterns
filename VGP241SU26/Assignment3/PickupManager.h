#pragma once
#include <Vector.h>
#include <KDTree.h>
#include <Vector3.h>
#include "PickUp.h"

class PickupManager
{
public:
	void Initialize(int size);
	void AddItem(PickupType pickupType, const Vector3& pos);
	const PickUp* GetClosestPickup(const Vector3& pos);
	void ObtainPickupsInRange(const Vector3& pos, float range, PickupType pickupType);
	void BuildTree();
	void Terminate();

private:
	Vector<PickUp> mPickups;
	KDTree<float, 3> mTree;
};