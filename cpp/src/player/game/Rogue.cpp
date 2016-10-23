#include "Rogue.hpp"

#include <collision/RectBody.hpp>
#include <graphics/GraphicsManager.hpp>

Rogue::Rogue(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ROGUE_GID)), player)
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
	return "(Rogue: body=(" + getBody()->toString() + "))";
}
