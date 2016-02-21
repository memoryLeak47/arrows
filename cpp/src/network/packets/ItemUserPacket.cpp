#include "ItemUserPacket.hpp"

#include "../../player/property/item/Item.hpp"
#include "../../misc/Debug.hpp"

ItemUserPacket::ItemUserPacket(const std::vector<char>& ids)
{
	setIDs(ids);
}

ItemUserPacket::ItemUserPacket()
	: itemIDs({-1, -1, -1})
{}

const std::vector<PlayerProperty*> ItemUserPacket::getPlayerProperties() const
{
	std::vector<PlayerProperty*> props;
	for (int i = 0; i < 3; i++)
	{
		if (itemIDs[i] == -1)
		{
			props.push_back(NULL);
		}
		else
		{
			props.push_back(Item::get(itemIDs[i]));
		}
	}
	return props;
}

void ItemUserPacket::setIDs(const std::vector<char>& ids)
{
	itemIDs = ids;
}

std::string ItemUserPacket::toString() const
{
	// TODO
	Debug::warn("ItemUserPacket::toString(): TODO");
	return "";
}

CID ItemUserPacket::getCID() const
{
	return ITEM_USER_PACKET_CID;
}
