#include "ChoosePlayerPropertyMenu.hpp"

ChoosePlayerPropertyMenu::ChoosePlayerPropertyMenu(LobbyMenu* lobbyMenu, PlayerPropertyUserPacket* packet, const std::vector<PlayerProperty*>& props)
	: chooseProperties(props)
{
	lobby = lobbyMenu;
	slotPacket = packet;
}
