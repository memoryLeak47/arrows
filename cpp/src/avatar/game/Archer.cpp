#include "Archer.hpp"

#include <collision/RectBody.hpp>
#include <graphics/GraphicsManager.hpp>

Archer::Archer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ARCHER_GID)), player)
{}

Archer::Archer(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID Archer::getCompressID() const
{
	return ARCHER_CID;
}

std::string Archer::getCompressString() const
{
	return GamePlayer::getCompressString();
}

float Archer::getCollisionPriority(Entity* e)
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* Archer::getTexture() const
{
	return GraphicsManager::getTexture(ARCHER_GID);
}

std::string Archer::toString() const
{
	return "(Archer: body=(" + getBody()->toString() + "))";
}
