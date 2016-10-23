#ifndef __LOBBYITEM_CLASS__
#define __LOBBYITEM_CLASS__

class Item;

#include <playerproperty/PlayerProperty.hpp>
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
		virtual int getMassStat() const;
		virtual float getHealthStat() const;
		virtual char getID() const override final;
		Item* createGameItem() const;
	private:
		void setID(char);
		static std::vector<LobbyItem*> items;
		char id;
};

#endif
