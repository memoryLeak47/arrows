#ifndef __ARCHERGAMEPLAYER_CLASS__
#define __ARCHERGAMEPLAYER_CLASS__

class CompressBuffer;
class GameVector;
class LobbyPlayer;
class Entity;

#include <player/GamePlayer.hpp>
#include <misc/compress/CompressID.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class ArcherGamePlayer : public GamePlayer
{
	public:
		ArcherGamePlayer(CompressBuffer*);
		ArcherGamePlayer(const GameVector&, const LobbyPlayer*);
		virtual ~ArcherGamePlayer() {}

		// compress
		CompressID getCompressID() const override;
		std::string getCompressString() const override;

		virtual float getCollisionPriority(Entity* e) override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
