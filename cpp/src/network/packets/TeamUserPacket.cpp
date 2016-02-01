#include "TeamUserPacket.hpp"

TeamUserPacket::TeamUserPacket(int id) : teamID(id)
{}

Team* TeamUserPacket::getTeam() const
{
	return Team::get(teamID);
}
