#include "HealthRing.hpp"

TextureID HealthRing::getIconTextureID() const
{
	return HEALTHRING_ICON_GID;
}

float HealthRing::getHealthStat() const
{
	return 10.f;
}

std::string HealthRing::getDescription() const
{
	return "ring of  health... no idea";
}
