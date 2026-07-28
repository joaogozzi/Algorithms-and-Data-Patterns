#include <iostream>
#include "Inventory.h"

int main()
{
    Inventory inventory;

    inventory.Initialize(100);
    inventory.DisplayInventory();

    return 0;
}