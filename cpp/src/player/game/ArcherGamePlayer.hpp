#ifndef __ARCHERGAMEPLAYER_CLASS__
#define __ARCHERGAMEPLAYER_CLASS__

#include <player/GamePlayer.hpp>

class ArcherGamePlayer : public GamePlayer
{
	public:
		ArcherGamePlayer(const GameVector&, const LobbyPlayer*);
		virtual float getCollisionPriority(Entity* e) override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
