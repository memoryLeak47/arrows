#ifndef __SKILLUSERPACKET_CLASS__
#define __SKILLUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class SkillUserPacket : public PlayerPropertyUserPacket
{
	private:
		char skillIDs[4];
};

#endif
