#include "PlayerPanelsSkillIcon.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <core/Main.hpp>
#include <player/property/skill/LobbySkill.hpp>
#include <menu/menues/ChoosePlayerPropertyMenu.hpp>
#include <menu/menues/LobbyMenu.hpp> // for SKILL_PHASE
#include <network/packets/SkillPacket.hpp>
#include <player/LobbyPlayer.hpp>
#include <network/packets/AvatarPacket.hpp>

PlayerPanelsSkillIcon::PlayerPanelsSkillIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r), number(n)
{}

int PlayerPanelsSkillIcon::getChoosePhase() const
{
	return SKILL_PHASE;
}

void PlayerPanelsSkillIcon::onClick(int mouseButton)
{
	if (isChoosable())
	{
		const std::vector<LobbySkill*>& skills = LobbySkill::getAllLobbySkillsByAvatarID(getLobbyMenu()->getLocalPlayer()->getAvatarPacket()->getAvatarID());
		std::vector<PlayerProperty*> tmp;
		for (unsigned int i = 0; i < skills.size(); i++)
		{
			tmp.push_back(skills[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), new SkillPacket(*getLobbyMenu()->getLocalPlayer()->getSkillPacket()), tmp));
	}
}

TextureID PlayerPanelsSkillIcon::getTextureID() const
{
	if ((getPlayer()->getSkillPacket() == NULL) ||
	    (getPlayer()->getSkillPacket()->getPlayerProperties()[number] == NULL))
	{
		return VOID_ICON_GID;
	}
	return getPlayer()->getSkillPacket()->getPlayerProperties()[number]->getIconTextureID();
}
