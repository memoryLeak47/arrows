#ifndef __LOCKPACKET_CLASS__
#define __LOCKPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LockPacket : public Packet
{
	public:
		LockPacket(bool);
		LockPacket(CompressBuffer*);
		virtual ~LockPacket() {}
		bool isLocked() const;
		std::string getCompressString() const override;
		CompressID getCompressID() const override;
	private:
		bool locked;
};

#endif
