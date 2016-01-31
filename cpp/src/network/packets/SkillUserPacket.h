#ifndef __SKILLUSERPACKET_CLASS__
#define __SKILLUSERPACKET_CLASS__

#include "UserPacket.h"

class SkillUserPacket : public UserPacket
{
	private:
		char skillIDs[4];
};

#endif
