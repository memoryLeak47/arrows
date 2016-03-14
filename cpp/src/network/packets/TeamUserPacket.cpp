#include "TeamUserPacket.hpp"

TeamUserPacket::TeamUserPacket(char id)
	: teamID(id)
{}

TeamUserPacket::TeamUserPacket(CompressBuffer* buffer)
	: teamID(buffer->cut(1)[0])
{}

Team* TeamUserPacket::getTeam() const
{
	return Team::get(teamID);
}

std::string TeamUserPacket::toString() const
{
	std::string s;
	s += teamID;
	return s;
}

CID TeamUserPacket::getCID() const
{
	return TEAM_USER_PACKET_CID;
}
