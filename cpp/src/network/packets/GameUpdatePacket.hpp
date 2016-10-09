#ifndef __GAMEUPDATEPACKET_CLASS__
#define __GAMEUPDATEPACKET_CLASS__

#include <network/Packet.hpp>

class CompressBuffer;

class GameUpdatePacket : public Packet
{
	public:
		GameUpdatePacket(CompressBuffer*);
		std::string toString() const override;
		CID getCID() const override;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
