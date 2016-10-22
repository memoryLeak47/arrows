#include "LockUserPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

LockUserPacket::LockUserPacket(bool locked) : locked(locked)
{}

LockUserPacket::LockUserPacket(CompressBuffer* buffer)
	: locked(buffer->cutBool())
{}

bool LockUserPacket::isLocked() const
{
	return locked;
}

std::string LockUserPacket::getCompressString() const
{
	return compressBool(isLocked());
}

CID LockUserPacket::getCID() const
{
	return LOCK_USER_PACKET_CID;
}
