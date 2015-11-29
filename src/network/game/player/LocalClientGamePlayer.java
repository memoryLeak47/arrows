/*
	Ist nur im Server vorhanden und dort in der Player Liste. Der Client Local Player ist NICHT von diesem Datentyp.
	Speichert alle Daten über einen Spieler.
*/
package network.game.player;

import java.util.LinkedList;

import network.lobby.LobbyPlayer;
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
		return new LocalClientGamePlayerFrameUpdate(null /* TODO convert getEffects()*/, getPlayerStats(), getCharges());
	}

	public void apply(ClientGamePlayerFrameUpdate update)
	{
		
	}	

	public void apply(LocalClientGamePlayerFrameUpdate update)
	{
		
	}

	// getter
	public LinkedList<Effect> getEffects() { return effects; }
	public PlayerStats getPlayerStats() { return playerStats; }
	public short[] getCharges() { return charges; }
}
