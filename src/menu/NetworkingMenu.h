#ifndef __NETWORKINGMENU_CLASS__
#define __NETWORKINGMENU_CLASS__

#include <SFML/Network.hpp>

#include "Menu.h"
class Packet;
class PacketAndIP;

class NetworkingMenu : public Menu
{
	public:
		NetworkingMenu();
		void tick();
		void receivePacket(Packet* p, const sf::IpAddress&);
		virtual void handlePacket(Packet* p, const sf::IpAddress&) = 0;
	protected:
		void send(Packet*, const sf::IpAddress&);
	private:
		void handleAllPackets();
		std::vector<PacketAndIP*>& getPackets(); // protected ?
		std::vector<PacketAndIP*> packets;
};

#include "../network/Packet.h"
#include "../network/PacketAndIP.h"

#endif
