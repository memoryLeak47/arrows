#include "LoginUserPacket.hpp"

LoginUserPacket::LoginUserPacket(const std::string& name, int rank) : name(name), rank(rank)
{}

std::string LoginUserPacket::toString() const
{
	return compressString(getName()) + compressInt(getRank());
}

CID LoginUserPacket::getCID() const
{
	return LOGIN_USER_PACKET_CID;
}

std::string LoginUserPacket::getName() const
{
	return name;

}

int LoginUserPacket::getRank() const
{
	return rank;
}
