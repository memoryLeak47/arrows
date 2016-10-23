#ifndef __LOCKUSERPACKET_CLASS__
#define __LOCKUSERPACKET_CLASS__

class CompressBuffer;

#include <network/packets/UserPacket.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LockUserPacket : public UserPacket
{
	public:
		LockUserPacket(bool);
		LockUserPacket(CompressBuffer*);
		virtual ~LockUserPacket() {}
		bool isLocked() const;
		std::string getCompressString() const override;
		CompressID getCompressID() const override;
	private:
		bool locked;
};

#endif
