package core.game;

import java.util.LinkedList;

import entity.MinimizedEntity;
import entity.entities.bullet.Bullet;
import entity.entities.bullet.MinimizedBullet;
import entity.entities.mob.Mob;
import entity.entities.cosmetic.Cosmetic;
import tilemap.LobbyTileMap;
import misc.Debug;
import misc.math.menu.MenuPosition;
import misc.game.effect.Effect;
import misc.game.effect.MinimizedEffect;
import network.game.player.GamePlayer;
import network.game.player.ServerGamePlayer;
import network.game.player.LocalClientGamePlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import network.lobby.LobbyPlayer;
import network.game.packets.EventPacket;
import network.game.packets.GameFrameUpdatePacket;

public class ServerGame extends Game
{
	private LinkedList<ServerGamePlayer> players = new LinkedList<ServerGamePlayer>();
	private LinkedList<Mob> mobs = new LinkedList<Mob>();
	private LinkedList<Bullet> bullets = new LinkedList<Bullet>();

	public ServerGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(lobbyMap);
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new ServerGamePlayer(player, getGameTileMap().getSpawnTilePositionByTeam(player.getTeam())));
		}
	}

	private LocalClientGamePlayerFrameUpdate getLocalClientGamePlayerFrameUpdateByID(int id)
	{
		return new LocalClientGamePlayerFrameUpdate(
			Effect.toMinimizedEffects(getPlayers().get(id).getEffects()),
			getPlayers().get(id).getPlayerStats(),
			getPlayers().get(id).getCharges());
	}

	public void handleEvent(EventPacket event, int id)
	{
		Debug.warn("ServerGame.handleEvent(): TODO");		
	}

	public void tick()
	{
		Debug.warn("ServerGame.tick(): TODO");		
	}

	// Getter

	@Override public LinkedList<GamePlayer> getUncastedPlayers()
	{
		Debug.warnIf(players == null, "ServerGame.getUncastedPlayers(): return null");
		LinkedList<GamePlayer> tmpPlayers = new LinkedList<GamePlayer>();
		for (GamePlayer player : players)
		{
			tmpPlayers.add((GamePlayer) player);
		}
		return tmpPlayers;
	}

	public LinkedList<ServerGamePlayer> getPlayers()
	{
		Debug.warnIf(players == null, "ServerGame.getPlayers(): return null");
		return players;
	}

	public LinkedList<Mob> getMobs()
	{
		Debug.warnIf(mobs == null, "ServerGame.getMobs(): return null");
		return mobs;
	}

	public LinkedList<Bullet> getBullets()
	{
		Debug.warnIf(bullets == null, "ServerGame.getMobs(): return null");
		return bullets;
	}

	public GameFrameUpdatePacket getGameFrameUpdatePacketByID(int id)
	{
		Debug.warn("ServerGame.getGameFrameUpdatePacketByID(): return null; TODO");		
		return null;
	}

	public LinkedList<MinimizedEntity> getMinimizedEntities()
	{
		LinkedList<MinimizedEntity> entityList = new LinkedList<MinimizedEntity>();

		// all Player
		for (ServerGamePlayer player : getPlayers())
		{
			entityList.add(player.toMinimizedEntity());
		}

		// all Mobs
		for (Mob mob : getMobs())
		{
			entityList.add(mob.toMinimizedEntity());
		}

		// all bullets
		for (Bullet bullet : getBullets())
		{
			entityList.add(bullet.toMinimizedEntity());
		}

		// all cosmetics
		for (Cosmetic cosmetic : getCosmetics())
		{
			entityList.add(cosmetic.toMinimizedEntity());
		}

		return entityList;
	}

	@Override protected int getLocalPlayerID() { return 0; }
}
