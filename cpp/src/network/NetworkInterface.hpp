#ifndef __NETWORKINTERFACE_CLASS__
#define __NETWORKINTERFACE_CLASS__

#include <SFML/Network.hpp>

class Packet;
class PacketAndIP;

class NetworkInterface
{
	public:
		NetworkInterface();
		virtual ~NetworkInterface();
		void handleAllPackets();
		void receivePacket(Packet* p, sf::IpAddress*);
		virtual void handlePacket(Packet* p, sf::IpAddress*) = 0;
	protected:
		void send(Packet*, sf::IpAddress*) const;
	private:
		std::vector<PacketAndIP*>& getPackets();
		std::vector<PacketAndIP*> packets;
};

#include <network/Packet.hpp>
#include <network/PacketAndIP.hpp>

#endif
