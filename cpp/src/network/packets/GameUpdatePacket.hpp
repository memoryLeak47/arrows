#ifndef __GAMEUPDATEPACKET_CLASS__
#define __GAMEUPDATEPACKET_CLASS__

#include <network/Packet.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>
#include <entity/Idler.hpp>

class CompressBuffer;

class GameUpdatePacket : public Packet
{
	public:
		GameUpdatePacket(const std::vector<GamePlayer*>&, const std::vector<Mob*>&, const std::vector<Idler*>&);
		GameUpdatePacket(CompressBuffer*);
		GameUpdatePacket();
		std::string getCompressString() const override;
		CID getCID() const override;

		const std::vector<GamePlayer*>& getPlayers() const;
		const std::vector<Mob*>& getMobs() const;
		const std::vector<Idler*>& getIdlers() const;
	private:
		std::vector<GamePlayer*> players;
		std::vector<Mob*> mobs;
		std::vector<Idler*> idlers;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
