#ifndef __AVATARUSERPACKET_CLASS__
#define __AVATARUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class AvatarUserPacket : public PlayerPropertyUserPacket
{
	private:
		char avatarID;
};

#endif
