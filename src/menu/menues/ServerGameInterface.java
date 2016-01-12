package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import game.ServerGame;
import entity.MinimizedEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import menu.menues.GameInterface;
import misc.Debug;
import network.Packet;
import menu.event.Event;
import network.game.packets.GameFrameUpdatePacket;
import network.game.packets.PlayerControlsUpdatePacket;
import player.ClientGamePlayerFrameUpdate;
import player.LocalClientGamePlayerFrameUpdate;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import tilemap.LobbyTileMap;

public class ServerGameInterface extends GameInterface
{
	public ServerGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(new ServerGame(map, lobbyPlayers));
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof PlayerControlsUpdatePacket)
		{
			getGame().getPlayers().get(ipToID(ip)).applyPlayerControlsUpdatePacket((PlayerControlsUpdatePacket) packet);
		}
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
		if (!getGame().isIniting())
			getGame().getPlayers().get(0).applyPlayerControlsUpdatePacket(getPlayerControlsUpdatePacket());
		super.tick();
		if (!getGame().isIniting())
			sendGameFrameUpdatePackets();
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

	@Override protected float[] getLocalPlayerCharges()
	{
		return ((ServerGamePlayer) getGame().getLocalPlayer()).getCharges();
	}

	private LinkedList<MinimizedBullet> getMinimizedBullets()
	{
		LinkedList<MinimizedBullet> tmp = new LinkedList<MinimizedBullet>();

		for (int i = 0; i < getGame().getBullets().size(); i++)
		{
			tmp.add((MinimizedBullet) getGame().getBullets().get(i).toMinimizedEntity());
		}
		return tmp;
	}

	private GameFrameUpdatePacket getGameFrameUpdatePacketByID(int id)
	{
		LinkedList<ClientGamePlayerFrameUpdate> updates = new LinkedList<ClientGamePlayerFrameUpdate>();
		for (int i = 0; i < getGame().getPlayers().size(); i++)
		{
			updates.add(getGame().getPlayers().get(i).toClientGamePlayerFrameUpdate());
		}
		return new GameFrameUpdatePacket(updates, getMinimizedBullets(), null, getGame().getPlayers().get(id).toLocalClientGamePlayerFrameUpdate());
	}
}
