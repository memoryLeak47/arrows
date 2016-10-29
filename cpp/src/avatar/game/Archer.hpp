#ifndef __ARCHER_CLASS__
#define __ARCHER_CLASS__

class CompressBuffer;
class GameVector;
class LobbyPlayer;
class Entity;
class RestrictedGameInterface;

#include <player/GamePlayer.hpp>
#include <misc/compress/CompressID.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class Archer : public GamePlayer
{
	public:
		Archer(CompressBuffer*);
		Archer(const GameVector&, const LobbyPlayer*, RestrictedGameInterface*);
		virtual ~Archer() {}

		// compress
		CompressID getCompressID() const override;
		std::string getCompressString() const override;

		virtual float getCollisionPriority(Entity* e) override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
