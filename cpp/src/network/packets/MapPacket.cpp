#include "MapPacket.hpp"

#include "../../misc/Debug.hpp"

MapPacket::MapPacket(const std::vector<std::vector<int>>& map)
	: map(map)
{}

MapPacket::MapPacket(CompressBuffer* buffer)
{
	Debug::time("Pre");
	map = buffer->cutMap();
	Debug::time("Post");
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
