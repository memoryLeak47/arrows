#include "LobbyPlayersPacket.hpp"

LobbyPlayersPacket::LobbyPlayersPacket(const std::vector<LobbyPlayer*>& players)
	: players(players)
{}

LobbyPlayersPacket::LobbyPlayersPacket(CompressBuffer* buffer)
{
	std::vector<void*> vec(buffer->cutVectorByCID(LOBBY_PLAYER_CID));
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		players.push_back(static_cast<LobbyPlayer*>(vec[i]));
	}
}

std::string LobbyPlayersPacket::toString() const
{
	std::vector<Compressable*> vec;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		vec.push_back(players[i]);
	}
	return compressVector(vec);
}

CID LobbyPlayersPacket::getCID() const
{
	return LOBBY_PLAYERS_PACKET_CID;
}

std::vector<LobbyPlayer*> LobbyPlayersPacket::getPlayers() const
{
	return players;
}
