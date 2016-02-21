#include "Item.hpp"

#include "../../../misc/Converter.hpp"
#include "../../../misc/Debug.hpp"
#include "items/HealthRing.hpp"

std::vector<Item*> Item::items;

void Item::init()
{
	items.push_back(new HealthRing());

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->setID(i);
	}
}

void Item::uninit()
{
	items.clear();
}

Item* Item::get(int id)
{
	Debug::warnIf(id < 0 || id >= getAmount(), "Item::get(): id(" + Converter::intToString(id) + ") out of range");
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

void Item::setID(char id)
{
	this->id = id;
}

char Item::getID() const
{
	return id;
}

int Item::getMassStat() const
{
	return 0;
}

float Item::getHealthStat() const
{
	return 0;
}
