#ifndef __USERPACKETWITHID_CLASS__
#define __USERPACKETWITHID_CLASS__

#include "../Packet.hpp"
#include "UserPacket.hpp"

class UserPacketWithID : public Packet
{
	public:
		UserPacketWithID(UserPacket*, int);
		int getID() const;
		UserPacket* getPacket() const;
		std::string toString() const override;
		CID getCID() const override;
	private:
		int id;
		UserPacket* packet;
};

#endif
