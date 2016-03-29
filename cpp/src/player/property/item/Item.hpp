#ifndef __ITEM_CLASS__
#define __ITEM_CLASS__

#include "../PlayerProperty.hpp"

class Item : public PlayerProperty
{
	public:
		virtual ~Item() {}
		static void init();
		static void uninit();
		static Item* get(int);
		static int getAmount();
		static const std::vector<Item*> getAllItems();
		char getID() const override;
		virtual int getMassStat() const;
		virtual float getHealthStat() const;
	private:
		void setID(char);
		static std::vector<Item*> items;
		char id;
};

#endif
