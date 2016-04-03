#include "ArcherGamePlayer.hpp"

ArcherGamePlayer::ArcherGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GraphicsManager::getGameSizeOf(ARCHER_GID)), player)
{}

sf::Texture* ArcherGamePlayer::getTexture() const
{
	return GraphicsManager::getTexture(ARCHER_GID);
}
