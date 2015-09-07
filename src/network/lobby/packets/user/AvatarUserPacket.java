package network.lobby.packets.user;

import game.avatar.Avatar;
import network.lobby.packets.UserPacket;

public class AvatarUserPacket extends UserPacket
{
	private byte avatarID;

	public AvatarUserPacket(byte id)
	{
		avatarID = id;
	}

	public AvatarUserPacket(AvatarUserPacket packet)
	{
		avatarID = packet.getAvatarID();
	}

	public Avatar getAvatar()
	{
		return Avatar.getByID(avatarID);
	}

	public byte getAvatarID()
	{
		return avatarID;
	}
}
