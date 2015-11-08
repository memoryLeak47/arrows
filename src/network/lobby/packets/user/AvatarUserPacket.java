package network.lobby.packets.user;

import playerproperty.avatar.Avatar;
import playerproperty.PlayerProperty;
import misc.Debug;
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

	public void assign(AvatarUserPacket avatarPacket)
	{
		// TODO fehlerabfragen
		avatarID = avatarPacket.avatarID;
	}

	// Setter
	@Override public void setIDs(byte[] ids)
	{
		avatarID = ids[0];
		if (ids.length != 1)
		{
			Debug.error("AvatarUserPacket.setIDs(): ids enthält mehr als eine id");
		}
	}

	// Getter
	public Avatar getAvatar() { return Avatar.getByID(avatarID); }
	public byte getAvatarID() { return avatarID; }
	@Override public PlayerProperty[] getPlayerProperty() { return new PlayerProperty[]{getAvatar()}; }
}
