#include "LockUserPacket.hpp"

LockUserPacket::LockUserPacket(bool locked) : locked(locked)
{}

bool LockUserPacket::isLocked() const
{
	return locked;
}
