#include "MapPacket.hpp"

MapPacket::MapPacket(const std::vector<std::vector<int>>& map)
	: map(map)
{}

MapPacket::MapPacket(CompressBuffer* buffer)
{
	map = buffer->cutMap();
}

std::vector<std::vector<int>> MapPacket::getInts() const
{
	return map;
}

CID MapPacket::getCID() const
{
	return MAP_PACKET_CID;
}

std::string MapPacket::toString() const
{
	return compressMap(getInts());
}
