#include "NetworkInterface.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>
#include <network/NetworkDevice.hpp>
#include <network/PacketAndIP.hpp>

NetworkInterface::NetworkInterface()
{
	Main::getNetworkDevice()->pushInterface(this);
}

NetworkInterface::~NetworkInterface()
{
	deleteAndClearVector(packets);
	Main::getNetworkDevice()->popInterface();
}

void NetworkInterface::handleAllPackets()
{
	for (unsigned int i = 0; i < packets.size(); i++)
	{
		handlePacket(packets[i]->getPacket(), packets[i]->getIP());
	}
	deleteAndClearVector(packets);
}

void NetworkInterface::send(Packet* packet, sf::IpAddress* ip) const
{
	Main::getNetworkDevice()->send(packet, ip);
}

void NetworkInterface::receivePacket(Packet* packet, sf::IpAddress* ip)
{
	packets.push_back(new PacketAndIP(packet, ip));
}
