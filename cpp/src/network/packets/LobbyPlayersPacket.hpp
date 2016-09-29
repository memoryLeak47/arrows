#ifndef __LOBBYPLAYERSPACKET_CLASS__
#define __LOBBYPLAYERSPACKET_CLASS__

#include <network/Packet.hpp>

class CompressBuffer;
class LobbyPlayer;

class LobbyPlayersPacket : public Packet
{
	public:
		LobbyPlayersPacket(const std::vector<LobbyPlayer*>&);
		LobbyPlayersPacket(CompressBuffer*);
		virtual ~LobbyPlayersPacket() {} // don't delete the LobbyPlayers
		std::vector<LobbyPlayer*> getPlayers() const;
		virtual std::string toString() const override;
		virtual CID getCID() const override;
	private:
		std::vector<LobbyPlayer*> players;
};

#include <misc/compress/CompressBuffer.hpp>
#include <player/LobbyPlayer.hpp>

#endif
