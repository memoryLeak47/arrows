#include "NetworkingMenu.h"

#include "../core/Main.h"

NetworkingMenu::NetworkingMenu()
{
	Main::getNetworkDevice()->setNetworkingMenu(this);
}

void NetworkingMenu::tick()
{
	Menu::tick();
	handleAllPackets();
}

void NetworkingMenu::handleAllPackets()
{
	for (int i = 0; i < packets.size(); i++)
	{
		handlePacket(packets[i]->getPacket(), packets[i]->getIP());
	}
}
