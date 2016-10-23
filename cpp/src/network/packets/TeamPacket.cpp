#include "TeamPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <player/property/Team.hpp>

TeamPacket::TeamPacket(char id)
	: teamID(id)
{}

TeamPacket::TeamPacket(CompressBuffer* buffer)
	: teamID(buffer->cut(1)[0])
{}

Team* TeamPacket::getTeam() const
{
	return Team::get(teamID);
}

std::string TeamPacket::getCompressString() const
{
	std::string s;
	s += teamID;
	return s;
}

CompressID TeamPacket::getCompressID() const
{
	return TEAM_PACKET_CID;
}
