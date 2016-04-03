#include "Rogue.hpp"

extern TextureID ROGUE_ICON_TID;
extern const int ROGUE_AID;

TextureID Rogue::getIconTextureID() const
{
	return ROGUE_ICON_TID;
}

char Rogue::getID() const
{
	return ROGUE_AID;
}

std::string Rogue::getDescription() const
{
	return "?";
}
