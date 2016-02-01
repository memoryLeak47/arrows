#include "TeamUserPacket.hpp"

Team* TeamUserPacket::getTeam() const
{
	return Team::get(teamID);
}
