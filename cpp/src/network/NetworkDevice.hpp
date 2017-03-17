#ifndef __NETWORKDEVICE_CLASS__
#define __NETWORKDEVICE_CLASS__

constexpr int PORT = 4242;

class Packet;
class NetworkInterface;

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <stack>

class NetworkDevice
{
	public:
		NetworkDevice(); // binds socket
		void send(Packet*, const sf::IpAddress& ip);
		void receive();

		void pushInterface(NetworkInterface* interface);
		void popInterface();
	private:
		NetworkInterface* getNetworkInterface() const;

		sf::UdpSocket socket;
		std::stack<NetworkInterface*> interfaceStack;
};

#endif
