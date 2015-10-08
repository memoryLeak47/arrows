package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import game.ClientGame;
import game.tilemap.LobbyTileMap;
import network.Packet;
import network.lobby.LobbyPlayer;

public class ClientGameInterface extends GameInterface
{
	public ClientGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(new ClientGame(map, lobbyPlayers));
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		// TODO
	}
}
