#ifndef __NETWORKINTERFACE_CLASS__
#define __NETWORKINTERFACE_CLASS__

class Packet;
class PacketAndIP;

#include <SFML/Network/IpAddress.hpp>
#include <vector>

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

#endif
