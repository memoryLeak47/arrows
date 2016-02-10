#include "PlayerPanelsSkillIcon.hpp"

extern int VOID_ICON;

PlayerPanelsSkillIcon::PlayerPanelsSkillIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r), number(n)
{}

int PlayerPanelsSkillIcon::getChoosePhase() const
{
	return SKILL_PHASE;
}

TextureID PlayerPanelsSkillIcon::getTextureID() const
{
	// TODO
	return VOID_ICON;
}
