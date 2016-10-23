#include "RogueGamePlayer.hpp"

#include <collision/RectBody.hpp>
#include <graphics/GraphicsManager.hpp>

RogueGamePlayer::RogueGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ROGUE_GID)), player)
{}

RogueGamePlayer::RogueGamePlayer(CompressBuffer* buffer)
	: GamePlayer(buffer)
{}

CompressID RogueGamePlayer::getCompressID() const
{
	return ROGUE_GAME_PLAYER_CID;
}

std::string RogueGamePlayer::getCompressString() const
{
	return GamePlayer::getCompressString();
}

float RogueGamePlayer::getCollisionPriority(Entity* e)
{
	if (e->getEntityType() == getEntityType())
	{
		return -0.4f;
	}
	return 1.f;
}

sf::Texture* RogueGamePlayer::getTexture() const
{
	return GraphicsManager::getTexture(ROGUE_GID);
}

std::string RogueGamePlayer::toString() const
{
	return "(RogueGamePlayer: body=(" + getBody()->toString() + "))";
}
