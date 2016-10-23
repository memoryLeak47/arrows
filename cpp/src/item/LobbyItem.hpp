#ifndef __LOBBYITEM_CLASS__
#define __LOBBYITEM_CLASS__

class Item;

#include <player/property/PlayerProperty.hpp>
#include <vector>

class LobbyItem : public PlayerProperty
{
	public:
		virtual ~LobbyItem() {}
		static void init();
		static void uninit();
		static LobbyItem* get(int);
		static int getAmount();
		static const std::vector<LobbyItem*> getAllLobbyItems();
		char getID() const override;
		virtual int getMassStat() const;
		virtual float getHealthStat() const;
		Item* createGameItem() const;
	private:
		void setID(char);
		static std::vector<LobbyItem*> items;
		char id;
};

#endif
