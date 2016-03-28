#ifndef __NETWORKINGMENU_CLASS__
#define __NETWORKINGMENU_CLASS__

#include <SFML/Network.hpp>

#include "Menu.hpp"

class Packet;
class PacketAndIP;

class NetworkingMenu : public Menu
{
	public:
		NetworkingMenu();
		virtual ~NetworkingMenu();
		void tick() override;
		void receivePacket(Packet* p, sf::IpAddress*);
		virtual void handlePacket(Packet* p, sf::IpAddress*) = 0;
		virtual bool isNetworkingMenu() const override;
	protected:
		void send(Packet*, sf::IpAddress*) const;
	private:
		void handleAllPackets();
		std::vector<PacketAndIP*>& getPackets();
		std::vector<PacketAndIP*> packets;
};

#include "../network/Packet.hpp"
#include "../network/PacketAndIP.hpp"

#endif
