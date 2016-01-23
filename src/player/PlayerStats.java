package player;

import misc.Debug;
import misc.compress.Compressable;
import misc.compress.Compressor;

public class PlayerStats implements Compressable
{
	// TODO fill

	public PlayerStats(PlayerStats stats)
	{
	}

	public PlayerStats() {}

	@Override public byte getCID() { return Compressor.PLAYER_STATS_CID; }
	@Override public byte[] compress() { return new byte[0]; }
}
