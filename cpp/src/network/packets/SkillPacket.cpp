#include "SkillPacket.hpp"

#include <misc/Global.hpp>
#include <player/property/skill/Skill.hpp>
#include <misc/compress/CompressBuffer.hpp>

SkillPacket::SkillPacket(const std::string& ids)
{
	setIDs(ids);
}

SkillPacket::SkillPacket(CompressBuffer* buffer)
	: skillIDs(buffer->cut(4))
{}

SkillPacket::SkillPacket()
	: skillIDs({-1, -1, -1, -1})
{}

bool SkillPacket::isValid() const
{
	return skillIDs[0] != -1 && skillIDs[1] != -1 && skillIDs[2] != -1 && skillIDs[3] != -1;
}

const std::vector<PlayerProperty*> SkillPacket::getPlayerProperties() const
{
	std::vector<PlayerProperty*> props;
	for (int i = 0; i < 4; i++)
	{
		if (skillIDs[i] == -1)
		{
			props.push_back(NULL);
		}
		else
		{
			props.push_back(Skill::get(skillIDs[i]));
		}
	}
	return props;
}

void SkillPacket::setIDs(const std::string& ids)
{
	skillIDs = ids;
}

std::string SkillPacket::getCompressString() const
{
	// TODO
	std::string s;
	for (int i = 0; i < 4; i++)
	{
		s += skillIDs[i];
	}
	return s;
}

CompressID SkillPacket::getCompressID() const
{
	return SKILL_PACKET_CID;
}
