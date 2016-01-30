#ifndef __NETWORKDEVICE_CLASS__
#define __NETWORKDEVICE_CLASS__

#define PORT 4242

#include <SFML/Network.hpp>

class Packet;
class NetworkingMenu;

class NetworkDevice
{
	public:
		NetworkDevice();
		void send(Packet*, const sf::IpAddress& ip);
		void receive();
	private:
		sf::UdpSocket socket;
};

#include "Packet.h"
#include "../menu/NetworkingMenu.h"

#endif
