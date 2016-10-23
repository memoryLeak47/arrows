#ifndef __DISCONNECTUSERPACKET_CLASS__
#define __DISCONNECTUSERPACKET_CLASS__

class CompressBuffer;

#include "UserPacket.hpp"
#include <string>
#include <misc/compress/CompressID.hpp>

class DisconnectUserPacket : public UserPacket
{
	public:
		DisconnectUserPacket();
		DisconnectUserPacket(CompressBuffer*);
		virtual ~DisconnectUserPacket() {}
		std::string getCompressString() const override;
		CompressID getCompressID() const;
};

#endif
