#include "Item.hpp"

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
