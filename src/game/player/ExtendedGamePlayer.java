/*
	Ist nur im Server vorhanden und dort in der Player Liste. Der Client Local Player ist NICHT von diesem Datentyp.
	Speichert alle Daten über einen Spieler.
*/

package game.player;

import network.lobby.LobbyPlayer;

public class ExtendedGamePlayer extends MinimizedGamePlayer
{
	public ExtendedGamePlayer(LobbyPlayer lobbyPlayer)
	{
		super(lobbyPlayer);
		// TODO
	}
}
