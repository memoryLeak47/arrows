package core.game;

import java.util.LinkedList;

import entity.MinimizedEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import network.game.player.ClientGamePlayer;
import network.game.player.GamePlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import tilemap.LobbyTileMap;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.game.packets.GameFrameUpdatePacket;

public class ClientGame extends Game
{
	private LinkedList<ClientGamePlayer> players;
	private LinkedList<MinimizedBullet> bullets = new LinkedList<MinimizedBullet>();
	private LocalClientGamePlayerFrameUpdate localPlayerUpdate;

	private final int localPlayerID;

	public ClientGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID)
	{
		super(lobbyMap);
		this.localPlayerID = localPlayerID;
		initCamera();

		players = new LinkedList<ClientGamePlayer>();
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new ClientGamePlayer(player));
		}
	}

	@Override public void tick() { }

	public void apply(GameFrameUpdatePacket updatePacket)
	{
		Debug.warnIf(updatePacket == null, "ClientGame.apply() updatePacket == null");
		Debug.warnIf(updatePacket.getBullets() == null, "ClientGame.apply(): bullets == null");
		Debug.warnIf(updatePacket.getLocalClientGamePlayerFrameUpdate() == null, "ClientGame.apply(): localClientGamePlayerFrameUpdate == null");

		for (int id = 0; id < getPlayers().size(); id++)
		{
			getPlayers().get(id).apply(updatePacket.getPlayerUpdates().get(id));
		}
		bullets = updatePacket.getBullets();
		localPlayerUpdate = updatePacket.getLocalClientGamePlayerFrameUpdate();
	}

	@Override public LinkedList<MinimizedEntity> getMinimizedEntities()
	{
		LinkedList<MinimizedEntity> entities = new LinkedList<MinimizedEntity>();
		for (ClientGamePlayer player : getPlayers())
		{
			entities.add(player);
		}
		for (MinimizedBullet bullet : getBullets())
		{
			entities.add(bullet);
		}
		return entities;
	}

	// getter
	@Override public LinkedList<GamePlayer> getUncastedPlayers()
	{
		Debug.warnIf(players == null, "ClientGame.getUncastedPlayers(): return null");
		LinkedList<GamePlayer> tmpPlayers = new LinkedList<GamePlayer>();
		for (GamePlayer player : players)
		{
			tmpPlayers.add((GamePlayer) player);
		}
		return tmpPlayers;
	}

	public LinkedList<ClientGamePlayer> getPlayers()
	{
		Debug.warnIf(players == null, "ClientGame.getPlayers(): return null");
		return players;
	}

	public LinkedList<MinimizedBullet> getBullets()
	{
		Debug.warnIf(bullets == null, "ClientGame.getBullets(): return null");
		return bullets;
	}

	@Override protected int getLocalPlayerID() { return localPlayerID; }
}
