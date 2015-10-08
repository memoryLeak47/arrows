package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import game.ServerGame;
import game.tilemap.LobbyTileMap;
import menu.menues.GameInterface;
import misc.Debug;
import network.Packet;
import network.game.packets.EventPacket;
import network.lobby.LobbyPlayer;

public class ServerGameInterface extends GameInterface
{
	public ServerGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(new ServerGame(map, lobbyPlayers));
	}
	
	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof EventPacket)
		{
			// TODO
		}
		else
		{
			Debug.note("ServerGameInterface got non-EventPacket"); // ignore packet
		}
	}
}
