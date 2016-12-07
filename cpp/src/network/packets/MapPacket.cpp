#include "MapPacket.hpp"

#include <misc/Global.hpp>
#include <misc/compress/CompressBuffer.hpp>

MapPacket::MapPacket(const std::vector<std::vector<TileID>>& map)
	: map(map)
{}

MapPacket::MapPacket(CompressBuffer* buffer)
{
	map = buffer->cutMap();
}

std::vector<std::vector<TileID>> MapPacket::getTileIDs() const
{
	return map;
}

CompressID MapPacket::getCompressID() const
{
	return MAP_PACKET_CID;
}

std::string MapPacket::getCompressString() const
{
	return compressMap(getTileIDs());
}
