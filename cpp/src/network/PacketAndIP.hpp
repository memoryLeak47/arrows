#ifndef __PACKETANDIP_CLASS__
#define __PACKETANDIP_CLASS__

#include <SFML/Network.hpp>

class Packet;

class PacketAndIP
{
	public:
		PacketAndIP(Packet*, sf::IpAddress*);
		virtual ~PacketAndIP();
		Packet* getPacket();
		sf::IpAddress* getIP();
	private:
		Packet* packet;
		sf::IpAddress* ip;
};

#include "Packet.hpp"

#endif
