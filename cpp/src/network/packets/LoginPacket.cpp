#include "LoginPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

LoginPacket::LoginPacket(const std::string& name, int rank) : name(name), rank(rank)
{}

LoginPacket::LoginPacket(CompressBuffer* buffer)
	: name(buffer->cutString()), rank(buffer->cutInt())
{}

std::string LoginPacket::getCompressString() const
{
	return compressString(getName()) + compressInt(getRank());
}

CompressID LoginPacket::getCompressID() const
{
	return LOGIN_PACKET_CID;
}

std::string LoginPacket::getName() const
{
	return name;
}

int LoginPacket::getRank() const
{
	return rank;
}
