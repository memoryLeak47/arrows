package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import core.Main;
import core.game.ClientGame;
import tilemap.LobbyTileMap;
import misc.Debug;
import network.Packet;
import network.game.packets.EventPacket;
import network.lobby.LobbyPlayer;

public class ClientGameInterface extends GameInterface
{
	private InetAddress serverIP;

	public ClientGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID, InetAddress serverIP)
	{
		super(new ClientGame(map, lobbyPlayers, localPlayerID));
		Debug.warnIf(serverIP == null, "ClientGameInterface.<init>(): serverIP is null");
		this.serverIP = serverIP;
	}

	private ClientGame getGame() { return (ClientGame) getUncastedGame(); }

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		Debug.warn("CGI.handlePacket(): TODO");
	}

	@Override public void render()
	{
		super.render();
	}

	@Override public void onEvent(EventPacket packet)
	{
		super.onEvent(packet);
		Main.getNetworkDevice().send(packet, serverIP);
	}
}
