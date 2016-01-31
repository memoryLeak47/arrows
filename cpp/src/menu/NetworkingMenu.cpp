#include "NetworkingMenu.hpp"

#include "../core/Main.hpp"

NetworkingMenu::NetworkingMenu()
{}

void NetworkingMenu::tick()
{
	Menu::tick();
	handleAllPackets();
}

void NetworkingMenu::send(Packet* packet, const sf::IpAddress& ip)
{
	Main::getNetworkDevice()->send(packet, ip);
}

void NetworkingMenu::receivePacket(Packet* packet, const sf::IpAddress& ip)
{
	packets.push_back(new PacketAndIP(packet, ip));
}

bool NetworkingMenu::isNetworkingMenu() const { return true; }

void NetworkingMenu::handleAllPackets()
{
	for (int i = 0; i < packets.size(); i++)
	{
		handlePacket(packets[i]->getPacket(), packets[i]->getIP());
	}
}
