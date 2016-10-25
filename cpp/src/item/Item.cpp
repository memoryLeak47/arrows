#include "Item.hpp"

#include <item/LobbyItem.hpp>

Item::Item(const LobbyItem* lobbyItem)
	: description(lobbyItem->getDescription()), iconTextureID(lobbyItem->getIconTextureID())
{}
