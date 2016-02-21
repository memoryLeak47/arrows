#include "HealthRing.hpp"

extern TextureID HEALTHRING_ICON;

TextureID HealthRing::getIconTextureID() const
{
	return HEALTHRING_ICON;
}

float HealthRing::getHealthStat() const
{
	return 10.f;
}

std::string HealthRing::getDescription() const
{
	return "ring of  health... no idea";
}
