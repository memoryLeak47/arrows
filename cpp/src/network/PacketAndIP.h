#ifndef __PACKETANDIP_CLASS__
#define __PACKETANDIP_CLASS__

#include <SFML/Network.hpp>

class Packet;

class PacketAndIP
{
	public:
		PacketAndIP(Packet*, const sf::IpAddress&);
		Packet* getPacket();
		const sf::IpAddress& getIP();
	private:
		Packet* packet;
		sf::IpAddress ip;
};

#include "Packet.h"

#endif
