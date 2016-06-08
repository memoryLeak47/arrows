#ifndef __ARCHERGAMEPLAYER_CLASS__
#define __ARCHERGAMEPLAYER_CLASS__

#include "../GamePlayer.hpp"

class ArcherGamePlayer : public GamePlayer
{
	public:
		ArcherGamePlayer(const GameVector&, const LobbyPlayer*);
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
