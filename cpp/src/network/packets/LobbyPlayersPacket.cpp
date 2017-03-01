#include "LobbyPlayersPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <player/LobbyPlayer.hpp>

LobbyPlayersPacket::LobbyPlayersPacket(const std::vector<LobbyPlayer*>& players)
	: players(players)
{}

LobbyPlayersPacket::LobbyPlayersPacket(CompressBuffer* buffer)
{
	std::vector<void*> vec(buffer->cutVectorByCompressID(CompressIDs::LOBBY_PLAYER));
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		players.push_back(static_cast<LobbyPlayer*>(vec[i]));
	}
}

std::string LobbyPlayersPacket::getCompressString() const
{
	std::vector<Compressable*> vec;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		vec.push_back(players[i]);
	}
	return compressVector(vec);
}

CompressID LobbyPlayersPacket::getCompressID() const
{
	return CompressIDs::LOBBY_PLAYERS_PACKET;
}

std::vector<LobbyPlayer*> LobbyPlayersPacket::getPlayers() const
{
	return players;
}
