#include "PacketAndIP.hpp"

PacketAndIP::PacketAndIP(Packet* packet, const sf::IpAddress& ipArg) : packet(packet)
{
	ip = ipArg;
}

PacketAndIP::~PacketAndIP()
{} // should not delete packet

Packet* PacketAndIP::getPacket()
{
	return packet;
}

const sf::IpAddress& PacketAndIP::getIP()
{
	return ip;
}
