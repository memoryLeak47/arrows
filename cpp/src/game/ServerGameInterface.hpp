#ifndef __SERVERGAMEINTERFACE_CLASS__
#define __SERVERGAMEINTERFACE_CLASS__

#include "GameInterface.hpp"

class LobbyPlayer;

class ServerGameInterface : public GameInterface
{
	public:
		ServerGameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&);
		virtual ~ServerGameInterface();
		void handlePacket(Packet*, sf::IpAddress*) override;
	protected:
		virtual GamePlayer* getLocalPlayer() const override;
		virtual void updateOtherGamers() override;
		void updateOtherGamersExceptFor(int i);
};

#include <player/LobbyPlayer.hpp>

#endif
