#include "SkillUserPacket.hpp"

#include "../../player/property/skill/Skill.hpp"
#include "../../misc/Debug.hpp"

SkillUserPacket::SkillUserPacket(const std::vector<char>& ids)
{
	setIDs(ids);
}

SkillUserPacket::SkillUserPacket()
	: skillIDs({-1, -1, -1, -1})
{}

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

void SkillUserPacket::setIDs(const std::vector<char>& ids)
{
	skillIDs = ids;
}

std::string SkillUserPacket::toString() const
{
	// TODO
	Debug::warn("SkillUserPacket::toString(): TODO");
	return "";
}

CID SkillUserPacket::getCID() const
{
	return SKILL_USER_PACKET_CID;
}
