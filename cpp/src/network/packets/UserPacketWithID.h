#ifndef __USERPACKETWITHID_CLASS__
#define __USERPACKETWITHID_CLASS__

#include "../Packet.h"
#include "UserPacket.h"

class UserPacketWithID : public Packet
{
	public:
		int getID() const;
		UserPacket* getPacket() const;
	private:
		int id;
		UserPacket* packet;
};

#endif
