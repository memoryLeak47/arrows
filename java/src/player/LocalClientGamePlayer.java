/*
	Nur der Client Local Player ist von diesem Datentyp.
*/

package player;

import java.util.LinkedList;

import player.LobbyPlayer;
import misc.Debug;
import effect.Effect;
import player.PlayerStats;

public class LocalClientGamePlayer extends ClientGamePlayer
{
	private LinkedList<Effect> effects = new LinkedList<Effect>();
	private PlayerStats playerStats;
	private float[] charges;

	public LocalClientGamePlayer(LobbyPlayer lobbyPlayer)
	{
		super(lobbyPlayer);
	}

	public LocalClientGamePlayerFrameUpdate toLocalClientGamePlayerFrameUpdate()
	{
		return new LocalClientGamePlayerFrameUpdate(Effect.toMinimizedEffects(getEffects()) , getPlayerStats(), getCharges());
	}

	public void apply(ClientGamePlayerFrameUpdate update)
	{
		Debug.warn("LocalClientGamePlayer.apply(): TODO");
	}	

	public void apply(LocalClientGamePlayerFrameUpdate update)
	{
		Debug.warn("LocalClientGamePlayer.apply(local): TODO");
	}

	// getter
	public LinkedList<Effect> getEffects() { return effects; }
	public PlayerStats getPlayerStats() { return playerStats; }
	public float[] getCharges() { return charges; }
}
