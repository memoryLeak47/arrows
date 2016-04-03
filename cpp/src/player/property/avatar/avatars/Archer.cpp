#include "Archer.hpp"

#include "../../../game/ArcherGamePlayer.hpp"

extern TextureID ARCHER_ICON_TID;
extern const int ARCHER_AID;

TextureID Archer::getIconTextureID() const
{
	return ARCHER_ICON_TID;
}

char Archer::getID() const
{
	return ARCHER_AID;
}

std::string Archer::getDescription() const
{
	return "legolas; enough said";
}

GamePlayer* Archer::createGamePlayer(const GameVector& pos, const LobbyPlayer* player) const
{
	return new ArcherGamePlayer(pos, player);
}
