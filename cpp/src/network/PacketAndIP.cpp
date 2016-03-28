#include "PacketAndIP.hpp"

PacketAndIP::PacketAndIP(Packet* packet, sf::IpAddress* ipArg) : packet(packet)
{
	ip = new sf::IpAddress(*ipArg);
}

PacketAndIP::~PacketAndIP()
{
	delete ip;
} // should not delete packet

Packet* PacketAndIP::getPacket()
{
	return packet;
}

sf::IpAddress* PacketAndIP::getIP()
{
	return ip;
}
