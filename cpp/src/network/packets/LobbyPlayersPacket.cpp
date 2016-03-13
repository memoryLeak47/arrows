#include "LobbyPlayersPacket.hpp"

LobbyPlayersPacket::LobbyPlayersPacket(const std::vector<LobbyPlayer*>& players)
	: players(players)
{}

LobbyPlayersPacket::LobbyPlayersPacket(CompressBuffer* buffer)
{
}

std::string LobbyPlayersPacket::toString() const
{
	return "";
}

CID LobbyPlayersPacket::getCID() const
{
	return LOBBY_PLAYERS_PACKET_CID;
}

std::vector<LobbyPlayer*> LobbyPlayersPacket::getPlayers() const
{
	return players;
}
