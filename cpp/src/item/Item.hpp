#ifndef __ITEM_CLASS__
#define __ITEM_CLASS__

class LobbyItem;

struct ItemGivethrough
{
	const LobbyItem* lobbyItem;
};

#include <string>
#include <graphics/TextureID.hpp>
#include <game/frame/FrameCloneable.hpp>
#include <game/message/MessageCommunicator.hpp>

class Item : public FrameCloneable, public MessageCommunicator
{
	public:
		Item(const ItemGivethrough&);
	private:
		std::string description;
		TextureID iconTextureID;
};

#endif
