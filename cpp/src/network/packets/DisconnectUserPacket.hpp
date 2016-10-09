#ifndef __DISCONNECTUSERPACKET_CLASS__
#define __DISCONNECTUSERPACKET_CLASS__

#include "UserPacket.hpp"

class CompressBuffer;

class DisconnectUserPacket : public UserPacket
{
	public:
		DisconnectUserPacket();
		DisconnectUserPacket(CompressBuffer*);
		virtual ~DisconnectUserPacket() {}
		std::string getCompressString() const override;
		CID getCID() const;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
