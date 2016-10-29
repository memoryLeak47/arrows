#ifndef __ROGUE_CLASS__
#define __ROGUE_CLASS__

class CompressBuffer;
class GameVector;
class LobbyPlayer;
class Entity;

#include <player/GamePlayer.hpp>
#include <misc/compress/CompressID.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class Rogue : public GamePlayer
{
	public:
		Rogue(CompressBuffer*);
		Rogue(const GameVector&, const LobbyPlayer*, RestrictedGameInterface*);
		virtual ~Rogue() {}

		// compress
		CompressID getCompressID() const override;
		std::string getCompressString() const override;

		virtual float getCollisionPriority(Entity* e) override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
