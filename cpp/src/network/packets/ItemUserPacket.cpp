#include "ItemUserPacket.hpp"

#include "../../player/property/item/Item.hpp"

const std::vector<PlayerProperty*> ItemUserPacket::getPlayerProperties() const
{
	std::vector<PlayerProperty*> props;
	for (int i = 0; i < 3; i++)
	{
		props.push_back(Item::get(itemIDs[i]));
	}
	return props;
}

void ItemUserPacket::setIDs(const std::vector<char>& ids)
{
	for (int i = 0; i < 3; i++)
	{
		itemIDs[i] = ids[i];
	}
}
