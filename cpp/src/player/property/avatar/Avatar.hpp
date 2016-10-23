#ifndef __AVATAR_CLASS__
#define __AVATAR_CLASS__

class Avatar;
class GamePlayer;
class GameVector;
class LobbyPlayer;

#include <player/property/PlayerProperty.hpp>
#include <vector>

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

		GamePlayer* createGamePlayer(const GameVector&, const LobbyPlayer*) const;
	private:
		static std::vector<Avatar*> avatars;
};

#endif
