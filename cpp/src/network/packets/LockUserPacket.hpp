#ifndef __LOCKUSERPACKET_CLASS__
#define __LOCKUSERPACKET_CLASS__

#include <string>

#include "UserPacket.hpp"

class CompressBuffer;

class LockUserPacket : public UserPacket
{
	public:
		LockUserPacket(bool);
		LockUserPacket(CompressBuffer*);
		bool isLocked() const;
		std::string toString() const override;
		CID getCID() const override;
	private:
		bool locked;
};

#include "../../misc/compress/CompressBuffer.hpp"

#endif
