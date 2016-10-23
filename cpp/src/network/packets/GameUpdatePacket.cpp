#include "GameUpdatePacket.hpp"

#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>
#include <entity/Idler.hpp>
#include <misc/compress/CompressBuffer.hpp>

GameUpdatePacket::GameUpdatePacket(const std::vector<GamePlayer*>& players_arg, const std::vector<Mob*>& mobs_arg, const std::vector<Idler*>& idlers_arg)
	: players(players_arg), mobs(mobs_arg), idlers(idlers_arg)
{}

GameUpdatePacket::GameUpdatePacket(CompressBuffer* buffer)
{
	int size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		players.push_back(dynamic_cast<GamePlayer*>(buffer->cutCompressable()));
	}

	size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		mobs.push_back(dynamic_cast<Mob*>(buffer->cutCompressable()));
	}

	size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		idlers.push_back(dynamic_cast<Idler*>(buffer->cutCompressable()));
	}
}

std::string GameUpdatePacket::getCompressString() const
{
	std::string s = compressInt(players.size());
	for (unsigned int i = 0; i < players.size(); i++)
	{
		s += players[i]->compress();
	}

	s += compressInt(mobs.size());
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		s += mobs[i]->compress();
	}

	s += compressInt(idlers.size());
	for (unsigned int i = 0; i < idlers.size(); i++)
	{
		s += idlers[i]->compress();
	}

	return s;
}

CompressID GameUpdatePacket::getCompressID() const
{
	return GAME_UPDATE_PACKET_CID;
}

const std::vector<GamePlayer*>& GameUpdatePacket::getPlayers() const
{
	return players;
}

const std::vector<Mob*>& GameUpdatePacket::getMobs() const
{
	return mobs;
}

const std::vector<Idler*>& GameUpdatePacket::getIdlers() const
{
	return idlers;
}
