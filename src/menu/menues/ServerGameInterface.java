package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import core.game.ServerGame;
import tilemap.LobbyTileMap;
import menu.menues.GameInterface;
import misc.Debug;
import network.Packet;
import network.game.packets.EventPacket;
import network.game.packets.GameFrameUpdatePacket;
import network.game.player.ClientGamePlayerFrameUpdate;
import network.game.player.LocalClientGamePlayerFrameUpdate;
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
			getGame().handleEvent((EventPacket) packet, ipToID(ip));
		else
		{
			Debug.warn("ServerGameInterface.handlePacket(): wrong packet: " + packet);
		}
	}

	@Override public void render()
	{
		super.render(); // TODO add more?
	}

	@Override public void tick()
	{
		super.tick();
		sendGameFrameUpdatePackets();
	}

	@Override public void onEvent(EventPacket packet)
	{
		super.onEvent(packet);
		getGame().handleEvent(packet, 0);
	}

	// private

	private ServerGame getGame() { return (ServerGame) getUncastedGame(); }

	private int ipToID(InetAddress ip)
	{
		for (int i = 1; i < getGame().getPlayers().size(); i++)
		{
			if (getGame().getPlayers().get(i).getIP().equals(ip))
				return i;
		}
		Debug.warn("ServerGameInterface.ipToID: no player with that ip");
		return -1;
	}

	private void sendGameFrameUpdatePackets()
	{
		for (int i = 1; i < getGame().getPlayers().size(); i++) // für all client-spieler
		{
			send(getGameFrameUpdatePacketByID(i), getGame().getPlayers().get(i).getIP());
		}
	}

	private GameFrameUpdatePacket getGameFrameUpdatePacketByID(int id)
	{
		LinkedList<ClientGamePlayerFrameUpdate> updates = new LinkedList<ClientGamePlayerFrameUpdate>();
		for (int i = 0; i < getGame().getPlayers().size(); i++)
		{
			updates.add(getGame().getPlayers().get(i).toClientGamePlayerFrameUpdate());
		}
		return new GameFrameUpdatePacket(updates, null, null, getGame().getPlayers().get(id).toLocalClientGamePlayerFrameUpdate());
	}

}
