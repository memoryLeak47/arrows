#ifndef __LOBBYAVATAR_CLASS__
#define __LOBBYAVATAR_CLASS__

class GamePlayer;
class GameVector;
class LobbyPlayer;

#include <player/property/PlayerProperty.hpp>
#include <vector>

class LobbyAvatar : public PlayerProperty
{
	public:
		virtual ~LobbyAvatar() {}

		static void init();
		static void uninit();
		static LobbyAvatar* get(int);
		static int getAmount();
		static const std::vector<LobbyAvatar*> getAllLobbyAvatars();
		virtual int getMassStat() const;
		virtual float getHealthStat() const;

		GamePlayer* createGamePlayer(const GameVector&, const LobbyPlayer*) const;
	private:
		static std::vector<LobbyAvatar*> avatars;
};

#endif
