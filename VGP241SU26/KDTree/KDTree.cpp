#include <iostream>
#include <KDTree.h>
#include <Vector2.h>
#include <string>

enum ItemType
{
    IT_HEALTH,
    IT_WELLNESS,
    IT_MONEY,
    IT_COUNT,
};

struct Item
{
    std::string name;
    ItemType type;
    Vector2 position;

    struct FilterByType
    {
        ItemType type;
        bool operator()(const void* data)
        {
            const Item* item = (const Item*)data;
            return item->type == type;
        }
    };
};

int main()
{
    Vector<Item> items;
    KDTree<float, 2> itemsLocations;
    int maxItems = 100;

    items.Resize(maxItems);

    for (int i = 0; i < maxItems; ++i)
    {
        items[i].name = "ItemName " + std::to_string(i);
        items[i].type = (ItemType)(rand() % IT_COUNT);

        switch (items[i].type)
        {
        case IT_HEALTH:
            items[i].name += " HEALTH";
            break;

        case IT_WELLNESS:
            items[i].name += " WELLNESS";
            break;

        case IT_MONEY:
            items[i].name += " MONEY";
            break;
        }

        items[i].position.x = (float)(rand() % 501);
        items[i].position.y = (float)(rand() % 501);

        itemsLocations.AddItem(&items[i].position.x, &items[i]);
    }

    itemsLocations.BuildTree();

    Vector2 minRange = { 200.0f, 200.0f };
    Vector2 maxRange = { 400.0f, 400.0f };

    Item::FilterByType filter;
    filter.type = IT_MONEY;

    Vector<const void*> itemsInRange;

    itemsLocations.FindInRange(itemsInRange, &minRange.x, &maxRange.x, filter);

    for (Vector<const void*>::Iterator iter = itemsInRange.Begin(); iter != itemsInRange.End(); ++iter)
    {
        const Item* item = (const Item*)(*iter);
        std::cout << "Item in Range: " << item->name << " (" << item->position.x << ", " << item->position.y << ")\n";
    }

    itemsLocations.Terminate();

    return 0;
}
