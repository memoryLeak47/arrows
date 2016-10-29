#include "Item.hpp"

#include <item/LobbyItem.hpp>

Item::Item(const ItemGivethrough& gt)
	: description(gt.lobbyItem->getDescription()), iconTextureID(gt.lobbyItem->getIconTextureID())
{}
