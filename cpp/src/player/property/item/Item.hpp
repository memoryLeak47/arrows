#ifndef __ITEM_CLASS__
#define __ITEM_CLASS__

#include "../PlayerProperty.hpp"

class Item : public PlayerProperty
{
	public:
		static void init();
		static void uninit();
		static Item* get(int);
		static int getAmount();
		static const std::vector<Item*> getAllItems();
	private:
		static std::vector<Item*> items;
};

#endif
