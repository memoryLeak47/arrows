#include "UserPacketWithID.hpp"

#include <core/Main.hpp>
#include <misc/compress/CompressBuffer.hpp>
#include "UserPacket.hpp"

UserPacketWithID::UserPacketWithID(UserPacket* packet, int id) : id(id), packet(packet)
{}

UserPacketWithID::UserPacketWithID(CompressBuffer* buffer)
{
	packet = static_cast<UserPacket*>(buffer->cutByCompressID((CompressID) buffer->cutChar()));
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

std::string UserPacketWithID::getCompressString() const
{
	std::string packetString = getPacket()->compress(); // yes with CompressID!
	std::string idString = compressInt(getID());
	return packetString + idString;
}

CompressID UserPacketWithID::getCompressID() const
{
	return USER_PACKET_WITH_ID_CID;
}
