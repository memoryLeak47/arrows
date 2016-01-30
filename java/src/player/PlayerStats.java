package player;

import misc.Debug;
import misc.compress.*;

public class PlayerStats implements Compressable
{
	// TODO fill

	public PlayerStats(PlayerStats stats)
	{
	}

	public PlayerStats() {}

	public PlayerStats(CompressBuffer buffer) {}

	@Override public byte getCID() { return Compressor.PLAYER_STATS_CID; }
	@Override public byte[] compress() { return new byte[0]; }
}
