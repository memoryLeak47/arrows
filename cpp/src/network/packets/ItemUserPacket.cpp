#include "ItemUserPacket.hpp"

#include "../../player/property/item/Item.hpp"

ItemUserPacket::ItemUserPacket(const std::vector<char>& ids)
{
	setIDs(ids);
}

ItemUserPacket::ItemUserPacket()
{}

const std::vector<PlayerProperty*> ItemUserPacket::getPlayerProperties() const
{
	std::vector<PlayerProperty*> props;
	for (int i = 0; i < 3; i++)
	{
		props.push_back(Item::get(itemIDs[i]));
	}
	const std::vector<PlayerProperty*> newprops(props);
	return newprops;
}

void ItemUserPacket::setIDs(const std::vector<char>& ids)
{
	itemIDs = ids;
}

std::string ItemUserPacket::toString() const
{
	// TODO
	return "";
}

CID ItemUserPacket::getCID() const
{
	return ITEM_USER_PACKET_CID;
}
