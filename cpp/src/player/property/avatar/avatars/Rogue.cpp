#include "Rogue.hpp"

extern TextureID ROGUE_ICON;
extern const int ROGUE_AID;

TextureID Rogue::getIconTextureID() const
{
	return ROGUE_ICON;
}

char Rogue::getID() const
{
	return ROGUE_AID;
}

std::string Rogue::getDescription() const
{
	return "?";
}
