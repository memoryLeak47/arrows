#ifndef __ITEMUSERPACKET_CLASS__
#define __ITEMUSERPACKET_CLASS__

#include "UserPacket.hpp"

class ItemUserPacket : public UserPacket
{
	private:
		char itemIDs[3];
};

#endif
