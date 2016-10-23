#ifndef __TEAMUSERPACKET_CLASS__
#define __TEAMUSERPACKET_CLASS__

class CompressBuffer;
class Team;

#include "UserPacket.hpp"
#include <string>
#include <misc/compress/CompressID.hpp>

class TeamUserPacket : public UserPacket
{
	public:
		TeamUserPacket(char);
		TeamUserPacket(CompressBuffer*);
		virtual ~TeamUserPacket() {}
		Team* getTeam() const;
		std::string getCompressString() const override;
		CompressID getCompressID() const override;
	private:
		char teamID;
};

#endif
