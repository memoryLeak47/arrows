#include "Archer.hpp"

extern TextureID ARCHER_ICON;

TextureID Archer::getIconTextureID() const
{
	return ARCHER_ICON;
}

std::string Archer::getDescription() const
{
	return "legolas; enough said";
}
