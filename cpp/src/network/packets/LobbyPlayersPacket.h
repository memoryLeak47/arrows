#ifndef __LOBBYPLAYERSPACKET_CLASS__
#define __LOBBYPLAYERSPACKET_CLASS__

#include "../Packet.h"

class LobbyPlayersPacket : public Packet
{
	private:
		std::vector<LobbyPlayer> players;
};

#endif
