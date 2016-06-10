#ifndef __CLIENTGAMEINTERFACE_CLASS__
#define __CLIENTGAMEINTERFACE_CLASS__

#include "GameInterface.hpp"

class LobbyPlayer;

class ClientGameInterface : public GameInterface
{
	public:
		ClientGameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&, int playerID, sf::IpAddress*);
		virtual ~ClientGameInterface();
		void handlePacket(Packet*, sf::IpAddress*) override;
	protected:
		virtual GamePlayer* getLocalPlayer() const override;
	private:
		sf::IpAddress* serverIP;
		unsigned int localPlayerID;
};

#include "../player/LobbyPlayer.hpp"

#endif
