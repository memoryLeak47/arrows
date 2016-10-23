#include "ArcherGamePlayer.hpp"

#include <collision/RectBody.hpp>
#include <graphics/GraphicsManager.hpp>

ArcherGamePlayer::ArcherGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ARCHER_GID)), player)
{}

ArcherGamePlayer::ArcherGamePlayer(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID ArcherGamePlayer::getCompressID() const
{
	return ARCHER_GAME_PLAYER_CID;
}

std::string ArcherGamePlayer::getCompressString() const
{
	return GamePlayer::getCompressString();
}

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
