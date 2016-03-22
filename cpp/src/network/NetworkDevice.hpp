#ifndef __NETWORKDEVICE_CLASS__
#define __NETWORKDEVICE_CLASS__

#define PORT 4242
#define MAX_PACKET_LENGTH 50

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

#include "Packet.hpp"
#include "../menu/NetworkingMenu.hpp"

#endif
