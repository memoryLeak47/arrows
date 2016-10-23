#include "TeamUserPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <player/property/Team.hpp>

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

std::string TeamUserPacket::getCompressString() const
{
	std::string s;
	s += teamID;
	return s;
}

CompressID TeamUserPacket::getCompressID() const
{
	return TEAM_USER_PACKET_CID;
}
