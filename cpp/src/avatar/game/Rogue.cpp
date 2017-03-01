#include "Rogue.hpp"

#include <entity/EntityGivethrough.hpp>
#include <graphics/GraphicsManager.hpp>
#include <collision/RectShape.hpp>

Rogue::Rogue(const GameVector& pos, const LobbyPlayer* player, RestrictedGameInterface* rgi)
	: GamePlayer(EntityGivethrough(new RectShape(this), pos, GraphicsManager::getGameSizeOf(GraphicsIDs::ROGUE)), player, rgi)
{}

Rogue::Rogue(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID Rogue::getCompressID() const
{
	return CompressIDs::ROGUE;
}

std::string Rogue::getCompressString() const
{
	return GamePlayer::getCompressString();
}

float Rogue::getCollisionPriority(Entity* e) const
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* Rogue::getTexture() const
{
	return GraphicsManager::getTexture(GraphicsIDs::ROGUE);
}

std::string Rogue::toString() const
{
	return "(Rogue)";
}
