#include "DisconnectUserPacket.hpp"

DisconnectUserPacket::DisconnectUserPacket()
{}

DisconnectUserPacket::DisconnectUserPacket(CompressBuffer* buffer)
{}

std::string DisconnectUserPacket::getCompressString() const
{
	return "";
}

CompressID DisconnectUserPacket::getCompressID() const
{
	return DISCONNECT_USER_PACKET_CID;
}
