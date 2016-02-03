#include "SkillIcon.hpp"

SkillIcon::SkillIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r), number(n)
{}

int SkillIcon::getChoosePhase() const
{
	return SKILL_PHASE;
}

ImageID SkillIcon::getImageID() const
{
	// TODO
	return ImageID(0, 0);
}
