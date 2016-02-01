#ifndef __LOCKUSERPACKET_CLASS__
#define __LOCKUSERPACKET_CLASS__

#include <string>

#include "UserPacket.hpp"

class LockUserPacket : public UserPacket
{
	public:
		LockUserPacket(bool);
		//compress TODO
		bool isLocked() const;
		std::string toString() const override;
		CID getCID() const override;
	private:
		bool locked;
};

#endif
