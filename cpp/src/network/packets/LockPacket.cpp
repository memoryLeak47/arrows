#include "LockPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

LockPacket::LockPacket(bool locked) : locked(locked)
{}

LockPacket::LockPacket(CompressBuffer* buffer)
	: locked(buffer->cutBool())
{}

bool LockPacket::isLocked() const
{
	return locked;
}

std::string LockPacket::getCompressString() const
{
	return compressBool(isLocked());
}

CompressID LockPacket::getCompressID() const
{
	return LOCK_PACKET_CID;
}
