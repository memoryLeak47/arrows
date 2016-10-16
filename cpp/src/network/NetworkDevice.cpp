#include "NetworkDevice.hpp"

#include "Packet.hpp"
#include <core/Main.hpp>
#include <misc/Debug.hpp>
#include <misc/Converter.hpp>

NetworkDevice::NetworkDevice()
{
	socket.setBlocking(false);
	socket.bind(PORT);
}

void NetworkDevice::send(Packet* packet, sf::IpAddress* ip)
{
	if (packet == NULL) Debug::warn("NetworkDevice::send(): packet is null");

	sf::Packet sfmlPacket;
	std::string string = packet->compress();
	sfmlPacket << string;

	if (socket.send(sfmlPacket, *ip, PORT) != sf::Socket::Done) // send
	{
		Debug::warn("NetworkDevice::send() failed");
	}
	else
	{
		if (global::PACKET_SOUND)
		{
			system("paplay /usr/share/sounds/ubuntu/notifications/Blip.ogg &");
		}

		if (string.length() > MAX_PACKET_LENGTH)
		{
			if (TAG_NETWORK) Debug::note("sent big packet with CID: " + Converter::intToString(string[0]));
		}
		else
		{
			if (TAG_NETWORK) Debug::note("sent packet with string: " + Converter::charsToString(string));
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

	if (global::PACKET_SOUND)
	{
		system("paplay /usr/share/sounds/ubuntu/stereo/message.ogg &");
	}

	std::string string;
	sfmlPacket >> string;

	if (string.length() > MAX_PACKET_LENGTH)
	{
		if (TAG_NETWORK) Debug::note("received big packet with CID: " + Converter::intToString(string[0]));
	}
	else
	{
		if (TAG_NETWORK) Debug::note("received packet with string: " + Converter::charsToString(string));
	}

	Packet* packet = (Packet*) Compressable::decompress(string);

	if (interfaceStack.empty())
	{
		Debug::warn("NetworkDevice::receive(): interfaceStack is empty");
	}
	else
	{
		getNetworkInterface()->receivePacket(packet, &ip);
	}
}

NetworkInterface* NetworkDevice::getNetworkInterface() const
{
	return interfaceStack.top();
}

void NetworkDevice::pushInterface(NetworkInterface* interface)
{
	interfaceStack.push(interface);
}

void NetworkDevice::popInterface()
{
	interfaceStack.pop();
}
