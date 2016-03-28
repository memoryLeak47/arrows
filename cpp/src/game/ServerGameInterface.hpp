#ifndef __SERVERGAMEINTERFACE_CLASS__
#define __SERVERGAMEINTERFACE_CLASS__

#include "GameInterface.hpp"

class LobbyPlayer;

class ServerGameInterface : public GameInterface
{
	public:
		ServerGameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&);
		void handlePacket(Packet*, sf::IpAddress*) override;
};

#include "../player/LobbyPlayer.hpp"

#endif
