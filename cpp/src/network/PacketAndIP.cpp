#include "PacketAndIP.hpp"

PacketAndIP::PacketAndIP(Packet* packet, const sf::IpAddress& ip) : packet(packet), ip(ip)
{}

Packet* PacketAndIP::getPacket()
{
	return packet;
}

const sf::IpAddress& PacketAndIP::getIP()
{
	return ip;
}
