#include "UserPacketWithID.hpp"

UserPacketWithID::UserPacketWithID(UserPacket* packet, int id) : packet(packet), id(id)
{}

UserPacketWithID::UserPacketWithID(CompressBuffer* buffer)
{
	packet = static_cast<UserPacket*>(buffer->cutByCID(buffer->cutChar()));
	id = buffer->cutInt();
}

int UserPacketWithID::getID() const
{
	return id;
}

UserPacket* UserPacketWithID::getPacket() const
{
	return packet;
}

std::string UserPacketWithID::toString() const
{
	std::string packetString = getPacket()->compress(); // yes with CID!
	std::string idString = compressInt(getID());
	return idString + packetString;
}

CID UserPacketWithID::getCID() const
{
	return USER_PACKET_WITH_ID_CID;
}
