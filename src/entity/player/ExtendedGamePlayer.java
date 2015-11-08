/*
	Ist nur im Server vorhanden und dort in der Player Liste. Der Client Local Player ist NICHT von diesem Datentyp.
	Speichert alle Daten über einen Spieler.
*/
package entity.player;

import java.net.InetAddress;

import network.lobby.LobbyPlayer;

public class ExtendedGamePlayer extends MinimizedGamePlayer
{
	private InetAddress ip;

	public ExtendedGamePlayer(LobbyPlayer lobbyPlayer)
	{
		super(lobbyPlayer);
		// TODO
	}

	public InetAddress getIP() { return ip; }
}
