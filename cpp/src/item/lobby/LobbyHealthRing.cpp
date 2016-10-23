#include "LobbyHealthRing.hpp"

TextureID LobbyHealthRing::getIconTextureID() const
{
	return HEALTHRING_ICON_GID;
}

float LobbyHealthRing::getHealthStat() const
{
	return 10.f;
}

std::string LobbyHealthRing::getDescription() const
{
	return "ring of  health... no idea";
}
