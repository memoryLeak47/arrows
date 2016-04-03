#include "HealthRing.hpp"

GraphicsID HealthRing::getIconGraphicsID() const
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
