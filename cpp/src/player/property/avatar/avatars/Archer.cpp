#include "Archer.hpp"

#include <player/game/ArcherGamePlayer.hpp>

extern int ARCHER_AID;

TextureID Archer::getIconTextureID() const
{
	return ARCHER_ICON_GID;
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
