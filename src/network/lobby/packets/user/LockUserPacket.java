package network.lobby.packets.user;

import misc.compress.Compressor;
import misc.Debug;
import network.lobby.packets.UserPacket;

public class LockUserPacket extends UserPacket
{
	private boolean locked;

	public LockUserPacket(boolean value)
	{
		locked = value;
	}

	public void assign(LockUserPacket lockPacket)
	{
		Debug.warnIf(lockPacket == null, "LockUserPacket.assign(null)");
		locked = lockPacket.locked;
	}

	public LockUserPacket(LockUserPacket packet)
	{
		locked = packet.isLocked();
	}

	public boolean isLocked()
	{
		return locked;
	}

	@Override public byte getCID() { return Compressor.LOCK_USER_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.compressBoolean(locked);
	}
}
