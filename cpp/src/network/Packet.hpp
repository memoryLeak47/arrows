#ifndef __PACKET_CLASS__
#define __PACKET_CLASS__

#include <misc/compress/Compressable.hpp>

class Packet : public Compressable
{
	public:
		virtual ~Packet() {}
};

#endif
