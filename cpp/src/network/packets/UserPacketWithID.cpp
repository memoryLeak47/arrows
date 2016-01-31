#include "UserPacketWithID.h"

int UserPacketWithID::getID() const
{
	return id;
}

UserPacket* UserPacketWithID::getPacket() const
{
	return packet;
}
