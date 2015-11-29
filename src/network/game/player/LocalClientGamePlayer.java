/*
	Ist nur im Server vorhanden und dort in der Player Liste. Der Client Local Player ist NICHT von diesem Datentyp.
	Speichert alle Daten über einen Spieler.
*/
package network.game.player;

import java.net.InetAddress;

import network.lobby.LobbyPlayer;

public class LocalClientGamePlayer extends ClientGamePlayer
{
	private InetAddress ip;

	public LocalClientGamePlayer(LobbyPlayer lobbyPlayer)
	{
		super(lobbyPlayer);
		// TODO
	}

	public InetAddress getIP() { return ip; }
}
