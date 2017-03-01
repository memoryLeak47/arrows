#include "ItemPacket.hpp"

#include <misc/Global.hpp>
#include <item/LobbyItem.hpp>
#include <misc/compress/CompressBuffer.hpp>

ItemPacket::ItemPacket(const std::string& ids)
{
	setIDs(ids);
}

ItemPacket::ItemPacket(CompressBuffer* buffer)
	: itemIDs(buffer->cut(3))
{}

ItemPacket::ItemPacket()
	: itemIDs({-1, -1, -1})
{}

bool ItemPacket::isValid() const
{
	return itemIDs[0] != -1 && itemIDs[1] != -1 && itemIDs[2] != 1;
}

const std::vector<PlayerProperty*> ItemPacket::getPlayerProperties() const
{
	std::vector<PlayerProperty*> props;
	for (int i = 0; i < 3; i++)
	{
		if (itemIDs[i] == -1)
		{
			props.push_back(nullptr);
		}
		else
		{
			props.push_back(LobbyItem::get(itemIDs[i]));
		}
	}
	return props;
}

void ItemPacket::setIDs(const std::string& ids)
{
	itemIDs = ids;
}

std::string ItemPacket::getCompressString() const
{
	std::string s;
	for (int i = 0; i < 3; i++)
	{
		s += itemIDs[i];
	}
	return s;
}

CompressID ItemPacket::getCompressID() const
{
	return CompressIDs::ITEM_PACKET;
}
