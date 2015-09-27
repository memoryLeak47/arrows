package network.lobby.packets.user;

import game.avatar.Avatar;
import game.PlayerProperty;
import network.lobby.packets.UserPacket;
import network.lobby.packets.PlayerPropertyUserPacket;

public class AvatarUserPacket extends UserPacket implements PlayerPropertyUserPacket
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

	@Override public PlayerProperty[] getPlayerProperty() { return new PlayerProperty[]{getAvatar()}; }
}
