#ifndef __ARCHER_CLASS__
#define __ARCHER_CLASS__

class GamePlayer;
class GameVector;
class LobbyPlayer;

#include <player/property/avatar/Avatar.hpp>
#include <graphics/TextureID.hpp>
#include <string>

class Archer : public Avatar
{
	public:
		virtual TextureID getIconTextureID() const override;
		char getID() const override;
		std::string getDescription() const;
		virtual GamePlayer* createGamePlayer(const GameVector&, const LobbyPlayer*) const override;
};

#endif
