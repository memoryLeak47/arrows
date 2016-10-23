#include "SkillUserPacket.hpp"

#include <misc/Global.hpp>
#include <player/property/skill/Skill.hpp>
#include <misc/compress/CompressBuffer.hpp>

SkillUserPacket::SkillUserPacket(const std::string& ids)
{
	setIDs(ids);
}

SkillUserPacket::SkillUserPacket(CompressBuffer* buffer)
	: skillIDs(buffer->cut(4))
{}

SkillUserPacket::SkillUserPacket()
	: skillIDs({-1, -1, -1, -1})
{}

bool SkillUserPacket::isValid() const
{
	return skillIDs[0] != -1 && skillIDs[1] != -1 && skillIDs[2] != -1 && skillIDs[3] != -1;
}

const std::vector<PlayerProperty*> SkillUserPacket::getPlayerProperties() const
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

void SkillUserPacket::setIDs(const std::string& ids)
{
	skillIDs = ids;
}

std::string SkillUserPacket::getCompressString() const
{
	// TODO
	std::string s;
	for (int i = 0; i < 4; i++)
	{
		s += skillIDs[i];
	}
	return s;
}

CompressID SkillUserPacket::getCompressID() const
{
	return SKILL_USER_PACKET_CID;
}
