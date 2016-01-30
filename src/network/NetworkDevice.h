#ifndef __NETWORKDEVICE_CLASS__
#define __NETWORKDEVICE_CLASS__

#include <SFML/Network.hpp>

class NetworkingMenu;

class NetworkDevice
{
	public:
		void receive();
		void setNetworkingMenu(NetworkingMenu*);
	private:
		sf::UdpSocket socket;
		NetworkingMenu* networkingMenu;
};

#include "../menu/NetworkingMenu.h"

#endif
