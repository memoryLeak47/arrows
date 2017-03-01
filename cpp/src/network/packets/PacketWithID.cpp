#include "PacketWithID.hpp"

#include <core/Main.hpp>
#include <misc/compress/CompressBuffer.hpp>

PacketWithID::PacketWithID(Packet* packet, int id) : id(id), packet(packet)
{}

PacketWithID::PacketWithID(CompressBuffer* buffer)
{
	packet = static_cast<Packet*>(buffer->cutByCompressID((CompressID) buffer->cutChar()));
	id = buffer->cutInt();
}

PacketWithID::~PacketWithID()
{} // should not delete packet, otherwise: 'double-free ERROR'

int PacketWithID::getID() const
{
	return id;
}

Packet* PacketWithID::getPacket() const
{
	return packet;
}

std::string PacketWithID::getCompressString() const
{
	std::string packetString = getPacket()->compress(); // yes with CompressID!
	std::string idString = compressInt(getID());
	return packetString + idString;
}

CompressID PacketWithID::getCompressID() const
{
	return CompressIDs::PACKET_WITH_ID;
}
