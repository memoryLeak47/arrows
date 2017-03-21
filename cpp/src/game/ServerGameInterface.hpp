#ifndef __SERVERGAMEINTERFACE_CLASS__
#define __SERVERGAMEINTERFACE_CLASS__

class LobbyTileMap;
class LobbyPlayer;
class Packet;
class GamePlayer;

#include "GameInterface.hpp"
#include <vector>
#include <SFML/Network/IpAddress.hpp>

class ServerGameInterface : public GameInterface
{
	public:
		ServerGameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&, long int startTime_arg);
		virtual ~ServerGameInterface();
		void handlePacket(Packet*, const sf::IpAddress&) override;
		virtual void subTick() override;
	protected:
		virtual GamePlayer* getLocalPlayer() const override;
};

#endif
