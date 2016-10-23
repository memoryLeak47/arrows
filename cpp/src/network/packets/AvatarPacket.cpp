#include "AvatarPacket.hpp"

#include <misc/Global.hpp>
#include <player/property/avatar/Avatar.hpp>
#include <misc/compress/CompressBuffer.hpp>

AvatarPacket::AvatarPacket(char c)
        : avatarID(c)
{}

AvatarPacket::AvatarPacket()
        : avatarID(-1)
{}

AvatarPacket::AvatarPacket(CompressBuffer* buffer)
{
	avatarID = buffer->cut(1)[0];
}

bool AvatarPacket::isValid() const
{
	return avatarID != -1;
}

const std::vector<PlayerProperty*> AvatarPacket::getPlayerProperties() const
{
        std::vector<PlayerProperty*> props;
	if (avatarID == -1)
	{
		props.push_back(NULL);
	}
	else
	{
		props.push_back(Avatar::get(avatarID));
	}
        return props;
}

void AvatarPacket::setIDs(const std::string& ids)
{
        avatarID = ids[0];
}

std::string AvatarPacket::getCompressString() const
{
	std::string s;
	s += avatarID;
	return s;
}

CompressID AvatarPacket::getCompressID() const
{
        return AVATAR_PACKET_CID;
}

char AvatarPacket::getAvatarID() const
{
	return avatarID;
}
