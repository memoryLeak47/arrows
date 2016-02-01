#ifndef __DISCONNECTUSERPACKET_CLASS__
#define __DISCONNECTUSERPACKET_CLASS__

#include "UserPacket.hpp"

class DisconnectUserPacket : public UserPacket
{
	public:
		std::string toString() const;
		CID getCID() const;
};

#endif
