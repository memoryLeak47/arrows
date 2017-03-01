#include "LobbyHealthRing.hpp"

TextureID LobbyHealthRing::getIconTextureID() const
{
	return GraphicsIDs::HEALTHRING_ICON;
}

float LobbyHealthRing::getHealthStat() const
{
	return 10.f;
}

std::string LobbyHealthRing::getDescription() const
{
	return "ring of  health... no idea";
}
