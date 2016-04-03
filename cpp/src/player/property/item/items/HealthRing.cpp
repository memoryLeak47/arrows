#include "HealthRing.hpp"

extern TextureID HEALTHRING_ICON_TID;

TextureID HealthRing::getIconTextureID() const
{
	return HEALTHRING_ICON_TID;
}

float HealthRing::getHealthStat() const
{
	return 10.f;
}

std::string HealthRing::getDescription() const
{
	return "ring of  health... no idea";
}
