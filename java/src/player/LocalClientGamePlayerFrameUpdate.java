/*
	Wird für Client-LocalPlayer vom Server zum Client geschickt und dort gespeichert.
*/

package player;

import java.util.LinkedList;

import effect.MinimizedEffect;
import misc.compress.*;
import player.PlayerStats;

public class LocalClientGamePlayerFrameUpdate implements Compressable
{
	private LinkedList<MinimizedEffect> effects = new LinkedList<MinimizedEffect>();
	private PlayerStats playerStats;
	private float[] charges;

	public LocalClientGamePlayerFrameUpdate(LinkedList<MinimizedEffect> effects, PlayerStats playerStats, float[] charges)
	{
		this.effects = new LinkedList<MinimizedEffect>(effects);
		this.playerStats = new PlayerStats(playerStats);
		this.charges = new float[charges.length];
		for (int i = 0; i < charges.length; i++)
		{
			this.charges[i] = charges[i];
		}
	}

	public LinkedList<MinimizedEffect> getMinimizedEffects() { return effects; }
	public PlayerStats getPlayerStats() { return playerStats; }
	public float[] getCharges() { return charges; }

	@SuppressWarnings("unchecked")
	public LocalClientGamePlayerFrameUpdate(CompressBuffer buffer)
	{
		effects = buffer.cutListByCID(Compressor.MINIMIZED_EFFECT_CID);
		playerStats = (PlayerStats) buffer.cutByCID(Compressor.PLAYER_STATS_CID);
		charges = buffer.cutFloatArray();
	}

	@Override public byte getCID() { return Compressor.LOCAL_CLIENT_GAME_PLAYER_FRAME_UPDATE_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			Compressor.compressList(getMinimizedEffects()),
			getPlayerStats().compress(),
			Compressor.compressFloatArray(getCharges())});
	}
}
