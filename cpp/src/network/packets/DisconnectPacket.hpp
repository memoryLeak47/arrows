#ifndef __DISCONNECTPACKET_CLASS__
#define __DISCONNECTPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class DisconnectPacket : public Packet
{
	public:
		DisconnectPacket();
		DisconnectPacket(CompressBuffer*);
		virtual ~DisconnectPacket() {}
		std::string getCompressString() const override;
		CompressID getCompressID() const;
};

#endif
