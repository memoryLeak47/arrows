#include "ClientLobbyMenu.hpp"

#include "../../core/Main.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip)
{
}

LobbyPlayer* ClientLobbyMenu::getLocalPlayer() const
{
	return NULL; // TODO
}

void ClientLobbyMenu::lockPressed() {}
void ClientLobbyMenu::disconnectPressed()
{
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team) {}
