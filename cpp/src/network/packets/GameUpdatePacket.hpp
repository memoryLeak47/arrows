#ifndef __GAMEUPDATEPACKET_CLASS__
#define __GAMEUPDATEPACKET_CLASS__

#include <network/Packet.hpp>

class GameUpdatePacket : public Packet
{
	public:
		CID getCID() const;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
