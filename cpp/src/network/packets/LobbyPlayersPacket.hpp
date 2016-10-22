#ifndef __LOBBYPLAYERSPACKET_CLASS__
#define __LOBBYPLAYERSPACKET_CLASS__

class LobbyPlayer;
class CompressBuffer;

#include <network/Packet.hpp>
#include <vector>
#include <string>
#include <misc/compress/Cid.hpp>

class LobbyPlayersPacket : public Packet
{
	public:
		LobbyPlayersPacket(const std::vector<LobbyPlayer*>&);
		LobbyPlayersPacket(CompressBuffer*);
		virtual ~LobbyPlayersPacket() {} // don't delete the LobbyPlayers
		std::vector<LobbyPlayer*> getPlayers() const;
		virtual std::string getCompressString() const override;
		virtual CID getCID() const override;
	private:
		std::vector<LobbyPlayer*> players;
};

#endif
