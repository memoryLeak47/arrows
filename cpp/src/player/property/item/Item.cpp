#include "Item.hpp"

#include "../../../misc/Debug.hpp"

std::vector<Item*> Item::items;

void Item::init()
{
	// items.push_back(); ..
}

void Item::uninit()
{
	items.clear();
}

Item* Item::get(int id)
{
	Debug::warnIf(id < 0 || id >= getAmount(), "Item::get(): id out of range");
	return items[id];
}

int Item::getAmount()
{
	return items.size();
}

const std::vector<Item*> Item::getAllItems()
{
	return items;
}
