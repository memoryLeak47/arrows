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

	private ServerGame getGame() { return (ServerGame) getUncastedGame(); }
	
	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		Debug.note("ServerGameInterface.handlePacket(): TODO"); // ignore packet
	}

	@Override public void render()
	{
		Debug.note("ServerGameInterface.render(): TODO");
	}

	@Override public void onEvent(EventPacket packet)
	{
		super.onEvent(packet);
		getGame().handleEvent(packet, 0);
	}

}
