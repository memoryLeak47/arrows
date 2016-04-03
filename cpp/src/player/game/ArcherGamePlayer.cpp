#include "ArcherGamePlayer.hpp"

ArcherGamePlayer::ArcherGamePlayer(const GameVector& pos, const LobbyPlayer* player)
	: GamePlayer(new RectBody(pos, GameVector(1,1)), player)
{}
