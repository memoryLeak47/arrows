#include "NetworkDevice.hpp"

#include "Packet.hpp"
#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../misc/Converter.hpp"

NetworkDevice::NetworkDevice()
{
	socket.setBlocking(false);
	socket.bind(PORT);
}

void NetworkDevice::send(Packet* packet, sf::IpAddress* ip)
{
	Debug::warnIf(packet == NULL, "NetworkDevice::send(): packet is null");

	sf::Packet sfmlPacket;
	std::string string = packet->compress();
	sfmlPacket << string;

	if (socket.send(sfmlPacket, *ip, PORT) != sf::Socket::Done) // send
	{
		Debug::warn("NetworkDevice::send() failed");
	}
	else
	{
		if (string.length() > MAX_PACKET_LENGTH)
		{
			Debug::noteIf(TAG_NETWORK, "sent big packet with CID: " + Converter::intToString(string[0]));
		}
		else
		{
			Debug::noteIf(TAG_NETWORK, "sent packet with string: " + Converter::charsToString(string));
		}
	}

	sfmlPacket.clear();
}

void NetworkDevice::receive()
{
	sf::Packet sfmlPacket;
	sf::IpAddress ip;
	unsigned short port;
	if (socket.receive(sfmlPacket, ip, port) != sf::Socket::Done)
	{
		return;
	}

	std::string string;
	sfmlPacket >> string;

	if (string.length() > MAX_PACKET_LENGTH)
	{
		Debug::noteIf(TAG_NETWORK, "received big packet with CID: " + Converter::intToString(string[0]));
	}
	else
	{
		Debug::noteIf(TAG_NETWORK, "received packet with string: " + Converter::charsToString(string));
	}

	Packet* packet = (Packet*) Compressable::decompress(string);

	if (Main::getMenuList()->getNetworkingMenu() != NULL)
	{
		Main::getMenuList()->getNetworkingMenu()->receivePacket(packet, &ip);
	}
}
