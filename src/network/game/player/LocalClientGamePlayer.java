/*
	Nur der Client Local Player ist von diesem Datentyp.
*/

package network.game.player;

import java.util.LinkedList;

import network.lobby.LobbyPlayer;
import misc.Debug;
import misc.game.effect.Effect;
import misc.game.PlayerStats;

public class LocalClientGamePlayer extends ClientGamePlayer
{
	private LinkedList<Effect> effects = new LinkedList<Effect>();
	private PlayerStats playerStats;
	private short[] charges;

	public LocalClientGamePlayer(LobbyPlayer lobbyPlayer)
	{
		super(lobbyPlayer);
	}

	public ClientGamePlayerFrameUpdate toClientGamePlayerFrameUpdate()
	{
		return new ClientGamePlayerFrameUpdate(getHealth(), getPosition(), getImageID());
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
	public short[] getCharges() { return charges; }
}
