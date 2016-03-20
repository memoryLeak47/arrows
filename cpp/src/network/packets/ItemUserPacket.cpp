#include "ItemUserPacket.hpp"

#include "../../player/property/item/Item.hpp"
#include "../../misc/Debug.hpp"

ItemUserPacket::ItemUserPacket(const std::string& ids)
{
	setIDs(ids);
}

ItemUserPacket::ItemUserPacket(CompressBuffer* buffer)
	: itemIDs(buffer->cut(3))
{}

ItemUserPacket::ItemUserPacket()
	: itemIDs({-1, -1, -1})
{}

bool ItemUserPacket::isValid() const
{
	return itemIDs[0] != -1 && itemIDs[1] != -1 && itemIDs[2] != 1;
}

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

void ItemUserPacket::setIDs(const std::string& ids)
{
	itemIDs = ids;
}

std::string ItemUserPacket::toString() const
{
	std::string s;
	for (int i = 0; i < 3; i++)
	{
		s += itemIDs[i];
	}
	return s;
}

CID ItemUserPacket::getCID() const
{
	return ITEM_USER_PACKET_CID;
}
