#ifndef __TEAMUSERPACKET_CLASS__
#define __TEAMUSERPACKET_CLASS__

class CompressBuffer;
class Team;

#include "UserPacket.hpp"
#include <string>
#include <misc/compress/Cid.hpp>

class TeamUserPacket : public UserPacket
{
	public:
		TeamUserPacket(char);
		TeamUserPacket(CompressBuffer*);
		virtual ~TeamUserPacket() {}
		Team* getTeam() const;
		std::string getCompressString() const override;
		CID getCID() const override;
	private:
		char teamID;
};

#endif
