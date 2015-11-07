package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import game.ClientGame;
import game.tilemap.LobbyTileMap;
import misc.Debug;
import network.Packet;
import network.game.packets.EventPacket;
import network.lobby.LobbyPlayer;

public class ClientGameInterface extends GameInterface
{
	public ClientGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID)
	{
		super(new ClientGame(map, lobbyPlayers, localPlayerID));
	}

	private ClientGame getGame() { return (ClientGame) getUncastedGame(); }

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		Debug.warn("CGI.handlePacket(): TODO");
	}

	@Override public void render()
	{
		Debug.warn("CGI.render(): TODO");
	}

	@Override public void onEvent(EventPacket packet)
	{
		super.onEvent(packet);
		Debug.warn("CGI.onEvent(): TODO");
	}

	
}
