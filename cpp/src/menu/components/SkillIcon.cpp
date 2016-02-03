#include "SkillIcon.hpp"

extern int VOID_ICON;

SkillIcon::SkillIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r), number(n)
{}

int SkillIcon::getChoosePhase() const
{
	return SKILL_PHASE;
}

TextureID SkillIcon::getTextureID() const
{
	// TODO
	return VOID_ICON;
}
