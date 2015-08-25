package network.lobby.packets.user;

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

	public byte getAvatarID()
	{
		return avatarID;
	}
}
