/*#ifndef __GAMEUPDATEPACKET_CLASS__
#define __GAMEUPDATEPACKET_CLASS__

class GamePlayer;
class Mob;
class Idler;
class CompressBuffer;

#include <network/Packet.hpp>
#include <vector>
#include <string>
#include <misc/compress/CompressID.hpp>

class GameUpdatePacket : public Packet
{
	public:
		GameUpdatePacket(const std::vector<GamePlayer*>&, const std::vector<Mob*>&, const std::vector<Idler*>&);
		GameUpdatePacket(CompressBuffer*); // cuts playerStrings.size, playerStrings, mobs.size, mobs, idlers.size, idlers
		virtual ~GameUpdatePacket() {}

		std::string getCompressString() const override; // puts playerStrings.size, playerStrings, mobs.size, mobs, idlers.size, idlers
		CompressID getCompressID() const override;

		const std::vector<std::string>& getPlayerStrings() const;
		const std::vector<Mob*>& getMobs() const;
		const std::vector<Idler*>& getIdlers() const;
	private:
		std::vector<std::string> playerStrings;
		std::vector<Mob*> mobs;
		std::vector<Idler*> idlers;
};

#endif
*/
