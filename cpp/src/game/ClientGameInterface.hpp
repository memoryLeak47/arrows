#ifndef __CLIENTGAMEINTERFACE_CLASS__
#define __CLIENTGAMEINTERFACE_CLASS__

class LobbyTileMap;
class LobbyPlayer;
class Packet;
class GamePlayer;
class Mob;
class Idler;

#include "GameInterface.hpp"
#include <vector>
#include <SFML/Network/IpAddress.hpp>
#include <controller/Actions.hpp>

class ClientGameInterface : public GameInterface
{
	public:
		ClientGameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&, int playerID, const sf::IpAddress&, long int unixTime_arg);
		virtual ~ClientGameInterface();
		void handlePacket(Packet*, const sf::IpAddress&) override;
		virtual void tick() override;
	protected:
		virtual GamePlayer* getLocalPlayer() const override;
	private:
		void applyGameUpdate(const std::vector<std::string>&, const std::vector<Mob*>&, const std::vector<Idler*>&);

		Actions serverActionsStatus;
		sf::IpAddress serverIP;
		unsigned int localPlayerID;
};

#endif
