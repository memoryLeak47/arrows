#ifndef __LOCKUSERPACKET_CLASS__
#define __LOCKUSERPACKET_CLASS__

#include "UserPacket.hpp"

class LockUserPacket : public UserPacket
{
	public:
		LockUserPacket(bool);
		//compress TODO
		bool isLocked() const;
	private:
		bool locked;
};

#endif
