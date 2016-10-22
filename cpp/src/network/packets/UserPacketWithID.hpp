#ifndef __USERPACKETWITHID_CLASS__
#define __USERPACKETWITHID_CLASS__

class UserPacket;
class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/Cid.hpp>

class UserPacketWithID : public Packet
{
	public:
		UserPacketWithID(UserPacket*, int);
		UserPacketWithID(CompressBuffer*);
		virtual ~UserPacketWithID(); // does not delete packet; otherwise: 'double-free ERROR'
		int getID() const;
		UserPacket* getPacket() const;
		std::string getCompressString() const override;
		CID getCID() const override;
	private:
		int id;
		UserPacket* packet;
};

#endif
