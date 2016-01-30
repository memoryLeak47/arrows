package network.lobby.packets.user;

import player.property.avatar.Avatar;
import player.property.PlayerProperty;
import misc.Debug;
import misc.compress.*;
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
		Debug.warnIf(avatarPacket == null, "AvatarUserPacket.assign(null)");
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

	// getter
	public Avatar getAvatar() { return Avatar.getByID(avatarID); }
	public byte getAvatarID() { return avatarID; }
	@Override public PlayerProperty[] getPlayerProperty() { return new PlayerProperty[]{getAvatar()}; }

	public AvatarUserPacket(CompressBuffer buffer)
	{
		avatarID = buffer.cutByte();
	}

	@Override public byte getCID() { return Compressor.AVATAR_USER_PACKET_CID; }
	@Override public byte[] compress()
	{
		return new byte[] {avatarID};
	}
}
