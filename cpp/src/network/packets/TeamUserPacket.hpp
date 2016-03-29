#ifndef __TEAMUSERPACKET_CLASS__
#define __TEAMUSERPACKET_CLASS__

#include "UserPacket.hpp"

class Team;
class CompressBuffer;

class TeamUserPacket : public UserPacket
{
	public:
		TeamUserPacket(char);
		TeamUserPacket(CompressBuffer*);
		virtual ~TeamUserPacket() {}
		Team* getTeam() const;
		std::string toString() const override;
		CID getCID() const override;
	private:
		char teamID;
};

#include "../../player/property/Team.hpp"
#include "../../misc/compress/CompressBuffer.hpp"

#endif
