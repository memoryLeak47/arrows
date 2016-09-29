#include "NetworkingMenu.hpp"

#include <core/Main.hpp>
#include <misc/Debug.hpp>

NetworkingMenu::NetworkingMenu()
{}

NetworkingMenu::~NetworkingMenu()
{
	deleteAndClearVector(packets);
}

void NetworkingMenu::tick()
{
	Menu::tick();
	handleAllPackets();
}

void NetworkingMenu::send(Packet* packet, sf::IpAddress* ip) const
{
	Main::getNetworkDevice()->send(packet, ip);
}

void NetworkingMenu::receivePacket(Packet* packet, sf::IpAddress* ip)
{
	packets.push_back(new PacketAndIP(packet, ip));
}

bool NetworkingMenu::isNetworkingMenu() const { return true; }

void NetworkingMenu::handleAllPackets()
{
	for (unsigned int i = 0; i < packets.size(); i++)
	{
		handlePacket(packets[i]->getPacket(), packets[i]->getIP());
	}
	deleteAndClearVector(packets);
}
