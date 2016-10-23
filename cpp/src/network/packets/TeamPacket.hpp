#ifndef __TEAMPACKET_CLASS__
#define __TEAMPACKET_CLASS__

class CompressBuffer;
class Team;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class TeamPacket : public Packet
{
	public:
		TeamPacket(char);
		TeamPacket(CompressBuffer*);
		virtual ~TeamPacket() {}
		Team* getTeam() const;
		std::string getCompressString() const override;
		CompressID getCompressID() const override;
	private:
		char teamID;
};

#endif
