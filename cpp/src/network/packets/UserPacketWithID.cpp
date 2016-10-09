#include "UserPacketWithID.hpp"

#include <core/Main.hpp>

UserPacketWithID::UserPacketWithID(UserPacket* packet, int id) : id(id), packet(packet)
{}

UserPacketWithID::UserPacketWithID(CompressBuffer* buffer)
{
	packet = static_cast<UserPacket*>(buffer->cutByCID((CID) buffer->cutChar()));
	id = buffer->cutInt();
}

UserPacketWithID::~UserPacketWithID()
{} // should not delete packet, otherwise: 'double-free ERROR'

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
	return packetString + idString;
}

CID UserPacketWithID::getCID() const
{
	return USER_PACKET_WITH_ID_CID;
}
