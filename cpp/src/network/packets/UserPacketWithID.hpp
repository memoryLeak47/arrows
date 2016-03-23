#ifndef __USERPACKETWITHID_CLASS__
#define __USERPACKETWITHID_CLASS__

#include "../Packet.hpp"
#include "UserPacket.hpp"

class CompressBuffer;

class UserPacketWithID : public Packet
{
	public:
		UserPacketWithID(UserPacket*, int);
		UserPacketWithID(CompressBuffer*);
		virtual ~UserPacketWithID(); // does not delete packet; otherwise: 'double-free ERROR'
		int getID() const;
		UserPacket* getPacket() const;
		std::string toString() const override;
		CID getCID() const override;
	private:
		int id;
		UserPacket* packet;
};

#include "../../misc/compress/CompressBuffer.hpp"

#endif
