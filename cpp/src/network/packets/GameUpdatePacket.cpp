#include "GameUpdatePacket.hpp"

#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>
#include <entity/Idler.hpp>
#include <misc/compress/CompressBuffer.hpp>

GameUpdatePacket::GameUpdatePacket(const std::vector<GamePlayer*>& players_arg, const std::vector<Mob*>& mobs_arg, const std::vector<Idler*>& idlers_arg)
	: mobs(mobs_arg), idlers(idlers_arg)
{
	for (unsigned int i = 0; i < players_arg.size(); i++)
	{
		playerStrings.push_back(players_arg[i]->getCompressString());	
	}
}

GameUpdatePacket::GameUpdatePacket(CompressBuffer* buffer)
{
	int size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		playerStrings.push_back(buffer->cutString());
	}

	size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		mobs.push_back(buffer->cutCompressable<Mob>());
	}

	size = buffer->cutInt();
	for (int i = 0; i < size; i++)
	{
		idlers.push_back(buffer->cutCompressable<Idler>());
	}
}

std::string GameUpdatePacket::getCompressString() const
{
	std::string s = compressInt(playerStrings.size());
	for (unsigned int i = 0; i < playerStrings.size(); i++)
	{
		s += compressString(playerStrings[i]);
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

const std::vector<std::string>& GameUpdatePacket::getPlayerStrings() const
{
	return playerStrings;
}

const std::vector<Mob*>& GameUpdatePacket::getMobs() const
{
	return mobs;
}

const std::vector<Idler*>& GameUpdatePacket::getIdlers() const
{
	return idlers;
}
