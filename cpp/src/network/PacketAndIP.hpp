#ifndef __PACKETANDIP_CLASS__
#define __PACKETANDIP_CLASS__

class Packet;

#include <SFML/Network/IpAddress.hpp>

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

#endif
