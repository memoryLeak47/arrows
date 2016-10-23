#ifndef __PACKETWITHID_CLASS__
#define __PACKETWITHID_CLASS__

class Packet;
class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class PacketWithID : public Packet
{
	public:
		PacketWithID(Packet*, int);
		PacketWithID(CompressBuffer*);
		virtual ~PacketWithID(); // does not delete packet; otherwise: 'double-free ERROR'
		int getID() const;
		Packet* getPacket() const;
		std::string getCompressString() const override;
		CompressID getCompressID() const override;
	private:
		int id;
		Packet* packet;
};

#endif
