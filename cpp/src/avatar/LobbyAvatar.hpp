#ifndef __LOBBYAVATAR_CLASS__
#define __LOBBYAVATAR_CLASS__

class GamePlayer;
class GameVector;
class LobbyPlayer;
class RestrictedGameInterface;

#include <playerproperty/PlayerProperty.hpp>
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

		virtual char getID() const override final;
		GamePlayer* createGamePlayer(const GameVector&, const LobbyPlayer*, RestrictedGameInterface*) const;
	private:
		void setID(char);
		static std::vector<LobbyAvatar*> avatars;
		char id;
};

#endif
