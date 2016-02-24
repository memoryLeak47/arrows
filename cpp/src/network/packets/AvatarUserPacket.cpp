#include "AvatarUserPacket.hpp"

#include "../../player/property/avatar/Avatar.hpp"
#include "../../misc/Debug.hpp"

AvatarUserPacket::AvatarUserPacket(char c)
        : avatarID(c)
{}

AvatarUserPacket::AvatarUserPacket()
        : avatarID(-1)
{}

const std::vector<PlayerProperty*> AvatarUserPacket::getPlayerProperties() const
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

void AvatarUserPacket::setIDs(const std::vector<char>& ids)
{
        avatarID = ids[0];
}

std::string AvatarUserPacket::toString() const
{
        // TODO
        Debug::warn("AvatarUserPacket::toString(): TODO");
        return "";
}

CID AvatarUserPacket::getCID() const
{
        return AVATAR_USER_PACKET_CID;
}

char AvatarUserPacket::getAvatarID() const
{
	return avatarID;
}
