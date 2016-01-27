#ifndef __NETWORK_DEVICE__
#define __NETWORK_DEVICE__

#include <SFML/Network.hpp>

class NetworkDevice
{
	public:
		void receive();
	private:
		sf::UdpSocket socket;
};

#endif
