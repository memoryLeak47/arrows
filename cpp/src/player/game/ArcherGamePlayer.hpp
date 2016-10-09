#ifndef __ARCHERGAMEPLAYER_CLASS__
#define __ARCHERGAMEPLAYER_CLASS__

#include <player/GamePlayer.hpp>

class ArcherGamePlayer : public GamePlayer
{
	public:
		ArcherGamePlayer(CompressBuffer*);
		ArcherGamePlayer(const GameVector&, const LobbyPlayer*);

		// compress
		CID getCID() const override;
		std::string getCompressString() const override;

		virtual float getCollisionPriority(Entity* e) override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
