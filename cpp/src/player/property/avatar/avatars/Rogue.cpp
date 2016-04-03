#include "Rogue.hpp"

extern int ROGUE_AID;

GraphicsID Rogue::getIconGraphicsID() const
{
	return ROGUE_ICON_GID;
}

char Rogue::getID() const
{
	return ROGUE_AID;
}

std::string Rogue::getDescription() const
{
	return "?";
}
