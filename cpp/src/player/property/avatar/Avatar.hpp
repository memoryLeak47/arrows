#ifndef __AVATAR_CLASS__
#define __AVATAR_CLASS__

#include <player/property/PlayerProperty.hpp>

class GamePlayer;
class GameVector;
class LobbyPlayer;

class Avatar : public PlayerProperty
{
	public:
		virtual ~Avatar() {}

		static void init();
		static void uninit();
		static Avatar* get(int);
		static int getAmount();
		static const std::vector<Avatar*> getAllAvatars();
		virtual int getMassStat() const;
		virtual float getHealthStat() const;

		virtual GamePlayer* createGamePlayer(const GameVector&, const LobbyPlayer*) const = 0; // XXX workaround
	private:
		static std::vector<Avatar*> avatars;
};

#include <math/game/GameVector.hpp>
#include <player/LobbyPlayer.hpp>

#endif
