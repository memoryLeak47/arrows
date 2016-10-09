#include "ArcherGamePlayer.hpp"

ArcherGamePlayer::ArcherGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ARCHER_GID)), player)
{}

ArcherGamePlayer::ArcherGamePlayer(CompressBuffer* buffer)
	: GamePlayer((Body*) buffer->cutCompressable())
{
	if (not (buffer->cut(1)[0] == PLAYER_CONTROLLER_CID))
		Debug::warn("ArcherGamePlayer::ArcherGamePlayer(buffer): expected PLAYER_CONTROLLER_CID");
}

CID ArcherGamePlayer::getCID() const
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
