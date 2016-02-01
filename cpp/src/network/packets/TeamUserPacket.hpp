#ifndef __TEAMUSERPACKET_CLASS__
#define __TEAMUSERPACKET_CLASS__

#include "UserPacket.hpp"

class Team;

class TeamUserPacket : public UserPacket
{
	public:
		TeamUserPacket(int);
		Team* getTeam() const;
	private:
		int teamID;
};

#include "../../player/property/Team.hpp"

#endif
