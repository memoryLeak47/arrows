#ifndef __NETWORKDEVICE_CLASS__
#define __NETWORKDEVICE_CLASS__

#define PORT 4242

#include <SFML/Network.hpp>
#include <stack>

class Packet;
class NetworkInterface;

class NetworkDevice
{
	public:
		NetworkDevice(); // binds socket
		void send(Packet*, sf::IpAddress* ip);
		void receive();

		void pushInterface(NetworkInterface* interface);
		void popInterface();
	private:
		NetworkInterface* getNetworkInterface() const;

		sf::UdpSocket socket;
		std::stack<NetworkInterface*> interfaceStack;
};

#include "Packet.hpp"
#include "NetworkInterface.hpp"

#endif
