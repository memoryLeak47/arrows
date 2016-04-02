/*
	std::vector<std::vector<int>> map:
		siehe GameTileMap
*/

#ifndef __MAPPACKET_CLASS__
#define __MAPPACKET_CLASS__

#include <vector>

#include "../Packet.hpp"

class CompressBuffer;

class MapPacket : public Packet
{
	public:
		MapPacket(const std::vector<std::vector<int>>&);
		MapPacket(CompressBuffer*);
		std::vector<std::vector<int>> getInts() const;
		virtual CID getCID() const override;
		virtual std::string toString() const override;
	private:
		std::vector<std::vector<int>> map; // Zweidimensionaler Vektor lol
};

#include "../../misc/compress/CompressBuffer.hpp"

#endif
