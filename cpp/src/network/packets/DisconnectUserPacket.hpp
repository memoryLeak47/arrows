#ifndef __DISCONNECTUSERPACKET_CLASS__
#define __DISCONNECTUSERPACKET_CLASS__

#include "UserPacket.hpp"

class CompressBuffer;

class DisconnectUserPacket : public UserPacket
{
	public:
		DisconnectUserPacket();
		DisconnectUserPacket(CompressBuffer*);
		std::string toString() const;
		CID getCID() const;
};

#include "../../misc/compress/CompressBuffer.hpp"

#endif
