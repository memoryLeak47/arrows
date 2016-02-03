#include "TeamUserPacket.hpp"

TeamUserPacket::TeamUserPacket(int id) : teamID(id)
{}

Team* TeamUserPacket::getTeam() const
{
	return Team::get(teamID);
}

std::string TeamUserPacket::toString() const
{
	return compressInt(teamID);
}

CID TeamUserPacket::getCID() const
{
	return TEAM_USER_PACKET_CID;
}
