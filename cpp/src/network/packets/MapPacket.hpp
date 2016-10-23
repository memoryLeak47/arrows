/*
	std::vector<std::vector<int>> map:
		siehe GameTileMap
*/

#ifndef __MAPPACKET_CLASS__
#define __MAPPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <vector>
#include <misc/compress/CompressID.hpp>
#include <string>

class MapPacket : public Packet
{
	public:
		MapPacket(const std::vector<std::vector<int>>&);
		MapPacket(CompressBuffer*);
		std::vector<std::vector<int>> getInts() const;
		virtual CompressID getCompressID() const override;
		virtual std::string getCompressString() const override;
	private:
		std::vector<std::vector<int>> map; // Zweidimensionaler Vektor lol
};

#endif
