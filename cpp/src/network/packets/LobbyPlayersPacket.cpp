#include "LobbyPlayersPacket.hpp"

LobbyPlayersPacket::LobbyPlayersPacket(const std::vector<LobbyPlayer*>& players)
	: players(players)
{}

std::vector<LobbyPlayer*> LobbyPlayersPacket::getPlayers() const
{
	return players;
}
