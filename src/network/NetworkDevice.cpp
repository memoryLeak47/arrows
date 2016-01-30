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
	sfmlPacket << packet; // TODO serialize
	if (socket.send(sfmlPacket, ip, PORT) != sf::Socket::Done) // send
	{
		Debug::warn("NetworkDevice::send() failed");
	}
	else
	{
		Debug::note("sent packet");
	}
	sfmlPacket.clear();
}

void NetworkDevice::receive()
{
/*
	sf::Packet sfmlPacket;
	sf::IpAddress ip;
	unsigned short port;
	socket.receive(sfmlPacket, ip, port);
	Packet packet;
	char* compressed;
	sfmlPacket >> compressed;
	Main::getMenuList()->getNetworkingMenu()->receivePacket(packet);
*/
}
