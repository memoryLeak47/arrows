#include "PacketAndIP.hpp"

PacketAndIP::PacketAndIP(Packet* packet, const sf::IpAddress& ip) : packet(packet), ip(ip)
{}

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
