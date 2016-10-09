#include "GameUpdatePacket.hpp"

GameUpdatePacket::GameUpdatePacket(CompressBuffer* buffer)
{
	Debug::warn("GameUpdatePacket::GameUpdatePacket(CompressBuffer*): TODO");
}

std::string GameUpdatePacket::getCompressString() const
{
	Debug::warn("GameUpdatePacket::toString(): TODO");
	return std::string();
}

CID GameUpdatePacket::getCID() const
{
	return GAME_UPDATE_PACKET_CID;
}
