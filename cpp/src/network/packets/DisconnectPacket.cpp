#include "DisconnectPacket.hpp"

DisconnectPacket::DisconnectPacket()
{}

DisconnectPacket::DisconnectPacket(CompressBuffer* buffer)
{}

std::string DisconnectPacket::getCompressString() const
{
	return "";
}

CompressID DisconnectPacket::getCompressID() const
{
	return DISCONNECT_PACKET_CID;
}
