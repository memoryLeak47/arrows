package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class LockUserPacket extends UserPacket
{
	private boolean locked;

	public LockUserPacket(boolean value)
	{
		locked = value;
	}

	public LockUserPacket(LockUserPacket packet)
	{
		locked = packet.isLocked();
	}

	public boolean isLocked()
	{
		return locked;
	}
}
