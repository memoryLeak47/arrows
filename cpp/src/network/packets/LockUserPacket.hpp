#ifndef __LOCKUSERPACKET_CLASS__
#define __LOCKUSERPACKET_CLASS__

class CompressBuffer;

#include <network/packets/UserPacket.hpp>
#include <string>
#include <misc/compress/Cid.hpp>

class LockUserPacket : public UserPacket
{
	public:
		LockUserPacket(bool);
		LockUserPacket(CompressBuffer*);
		virtual ~LockUserPacket() {}
		bool isLocked() const;
		std::string getCompressString() const override;
		CID getCID() const override;
	private:
		bool locked;
};

#endif
