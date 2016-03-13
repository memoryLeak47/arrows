#ifndef __LOBBYPLAYERSPACKET_CLASS__
#define __LOBBYPLAYERSPACKET_CLASS__

#include "../Packet.hpp"

class LobbyPlayer;

class LobbyPlayersPacket : public Packet
{
	public:
		LobbyPlayersPacket(const std::vector<LobbyPlayer*>&);
		std::vector<LobbyPlayer*> getPlayers() const;
	private:
		std::vector<LobbyPlayer*> players;
};

#include "../../player/LobbyPlayer.hpp"

#endif
