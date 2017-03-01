#include "Archer.hpp"

#include <graphics/GraphicsManager.hpp>
#include <entity/EntityGivethrough.hpp>
#include <collision/RectShape.hpp>

Archer::Archer(const GameVector& pos, const LobbyPlayer* player, RestrictedGameInterface* rgi)
	: GamePlayer(EntityGivethrough(new RectShape(this), pos, GraphicsManager::getGameSizeOf(GraphicsIDs::ARCHER)), player, rgi)
{}

Archer::Archer(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID Archer::getCompressID() const
{
	return CompressIDs::ARCHER;
}

std::string Archer::getCompressString() const
{
	return GamePlayer::getCompressString();
}

float Archer::getCollisionPriority(Entity* e) const
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* Archer::getTexture() const
{
	return GraphicsManager::getTexture(GraphicsIDs::ARCHER);
}

std::string Archer::toString() const
{
	return "(Archer)";
}
