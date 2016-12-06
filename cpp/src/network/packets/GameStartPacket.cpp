#include "GameStartPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

GameStartPacket::GameStartPacket(long arg)
	: unixBeginTime(arg)
{}

GameStartPacket::GameStartPacket(CompressBuffer* buffer)
	: unixBeginTime(buffer->cutLong())
{}

std::string GameStartPacket::getCompressString() const
{
	return compressLong(unixBeginTime);
}

CompressID GameStartPacket::getCompressID() const
{
	return GAME_START_PACKET_CID;
}

long GameStartPacket::getUnixBeginTime() const
{
	return unixBeginTime;
}

