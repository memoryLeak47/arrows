#include "ArcherGamePlayer.hpp"

ArcherGamePlayer::ArcherGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ARCHER_GID)), player)
{}

float ArcherGamePlayer::getCollisionPriority(Entity* e)
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* ArcherGamePlayer::getTexture() const
{
	return GraphicsManager::getTexture(ARCHER_GID);
}

std::string ArcherGamePlayer::toString() const
{
	return "(ArcherGamePlayer: body=(" + getBody()->toString() + "))";
}
