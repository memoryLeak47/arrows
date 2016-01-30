#include "NetworkDevice.h"

#include "Packet.h"
#include "../core/Main.h"
#include "../misc/Debug.h"

NetworkDevice::NetworkDevice()
{
	socket.setBlocking(false);
	socket.bind(PORT);
}

void NetworkDevice::send(Packet* packet, const sf::IpAddress& ip)
{
	Debug::warnIf(packet == NULL, "NetworkDevice::send(): packet is null");

	sf::Packet sfmlPacket;
	std::string string = packet->toString();
	sfmlPacket << string;

	if (socket.send(sfmlPacket, ip, PORT) != sf::Socket::Done) // send
	{
		Debug::warn("NetworkDevice::send() failed");
	}
	else
	{
		Debug::note("sent packet with string: " + string);
	}

	sfmlPacket.clear();
}

void NetworkDevice::receive()
{
	sf::Packet sfmlPacket;
	sf::IpAddress ip;
	unsigned short port;
	socket.receive(sfmlPacket, ip, port);

	std::string string;
	sfmlPacket >> string;

	Packet* packet = (Packet*) Compressable::decompress(string);
	Main::getMenuList()->getNetworkingMenu()->receivePacket(packet, ip);
}
