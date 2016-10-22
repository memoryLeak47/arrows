#ifndef __GAMEUPDATEPACKET_CLASS__
#define __GAMEUPDATEPACKET_CLASS__

class GamePlayer;
class Mob;
class Idler;
class CompressBuffer;

#include <network/Packet.hpp>
#include <vector>
#include <string>
#include <misc/compress/Cid.hpp>

class GameUpdatePacket : public Packet
{
	public:
		GameUpdatePacket(const std::vector<GamePlayer*>&, const std::vector<Mob*>&, const std::vector<Idler*>&);
		GameUpdatePacket(CompressBuffer*); // cuts players.size, players, mobs.size, mobs, idlers.size, idlers
		virtual ~GameUpdatePacket() {}

		std::string getCompressString() const override; // puts players.size, players, mobs.size, mobs, idlers.size, idlers
		CID getCID() const override;

		const std::vector<GamePlayer*>& getPlayers() const;
		const std::vector<Mob*>& getMobs() const;
		const std::vector<Idler*>& getIdlers() const;
	private:
		std::vector<GamePlayer*> players;
		std::vector<Mob*> mobs;
		std::vector<Idler*> idlers;
};

#endif
