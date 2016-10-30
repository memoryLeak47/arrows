#include "Rogue.hpp"

#include <entity/EntityGivethrough.hpp>
#include <graphics/GraphicsManager.hpp>

Rogue::Rogue(const GameVector& pos, const LobbyPlayer* player, RestrictedGameInterface* rgi)
	: GamePlayer(EntityGivethrough(pos, GraphicsManager::getGameSizeOf(ROGUE_GID)), player, rgi)
{}

Rogue::Rogue(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID Rogue::getCompressID() const
{
	return ROGUE_CID;
}

std::string Rogue::getCompressString() const
{
	return GamePlayer::getCompressString();
}

float Rogue::getCollisionPriority(Entity* e)
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* Rogue::getTexture() const
{
	return GraphicsManager::getTexture(ROGUE_GID);
}

std::string Rogue::toString() const
{
	return "(Rogue)";
}
