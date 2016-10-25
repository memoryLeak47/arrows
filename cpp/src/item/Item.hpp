#ifndef __ITEM_CLASS__
#define __ITEM_CLASS__

class LobbyItem;

#include <string>
#include <graphics/TextureID.hpp>

class Item
{
	public:
		Item(const LobbyItem*);
	private:
		std::string description;
		TextureID iconTextureID;
};

#endif
