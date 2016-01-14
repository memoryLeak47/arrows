package game;

import java.util.LinkedList;

import entity.MinimizedEntity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import entity.entities.dynamic.mob.ExtendedMob;
import entity.entities.dynamic.spinnable.cosmetic.ExtendedCosmetic;
import tilemap.LobbyTileMap;
import misc.Debug;
import misc.math.Camera;
import misc.math.pixel.PixelPosition;
import effect.Effect;
import effect.MinimizedEffect;
import player.GamePlayer;
import player.ServerGamePlayer;
import player.LocalClientGamePlayerFrameUpdate;
import player.LobbyPlayer;
import menu.event.Event;
import network.game.packets.GameFrameUpdatePacket;

public class ServerGame extends Game
{
	private LinkedList<ServerGamePlayer> players = new LinkedList<ServerGamePlayer>();
	private LinkedList<ExtendedMob> mobs = new LinkedList<ExtendedMob>();
	private LinkedList<ExtendedBullet> bullets = new LinkedList<ExtendedBullet>();
	private boolean initing = true;

	public ServerGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(lobbyMap);
		initCamera();
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(player.getAvatar().createServerGamePlayer(player, getGameTileMap().getSpawnTilePositionByTeam(player.getTeam())));
		}
		initing = false;
	}

	private LocalClientGamePlayerFrameUpdate getLocalClientGamePlayerFrameUpdateByID(int id)
	{
		return new LocalClientGamePlayerFrameUpdate(
			Effect.toMinimizedEffects(getPlayers().get(id).getEffects()),
			getPlayers().get(id).getPlayerStats(),
			getPlayers().get(id).getCharges());
	}

	public void tick()
	{
		// tick Entities
		// GameTileMap wird noch nicht getickt TODO

		int i;
		for (i=0; i < getBullets().size(); i++)
		{
			if (getBullets().get(i).hasToBeRemoved())
			{
				getBullets().remove(i);
				continue;
			}
			getBullets().get(i).tick();
		}
		for (i=0; i < getMobs().size(); i++)
		{
			if (getMobs().get(i).hasToBeRemoved())
			{
				getMobs().remove(i);
				continue;
			}
			getMobs().get(i).tick();
		}
		for (i=0; i < getPlayers().size(); i++)
		{
			getPlayers().get(i).tick();
		}
		for (i=0; i < getCosmetics().size(); i++)
		{
			if (getCosmetics().get(i).hasToBeRemoved())
			{
				getCosmetics().remove(i);
				continue;
			}
			getCosmetics().get(i).tick();
		}
	}

	public void addBullet(ExtendedBullet bullet)
	{
		Debug.warnIf(bullet == null, "Game.addBullet(): bullet == null");
		getBullets().add(bullet);
	}

	// getter

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

	public LinkedList<ExtendedMob> getMobs()
	{
		Debug.warnIf(mobs == null, "ServerGame.getMobs(): return null");
		return mobs;
	}

	public LinkedList<ExtendedBullet> getBullets()
	{
		Debug.warnIf(bullets == null, "ServerGame.getMobs(): return null");
		return bullets;
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
		for (ExtendedMob mob : getMobs())
		{
			entityList.add(mob.toMinimizedEntity());
		}

		// all bullets
		for (ExtendedBullet bullet : getBullets())
		{
			entityList.add(bullet.toMinimizedEntity());
		}

		// all cosmetics
		for (ExtendedCosmetic cosmetic : getCosmetics())
		{
			entityList.add(cosmetic.toMinimizedEntity());
		}

		return entityList;
	}

	public boolean isIniting() { return initing; }

	@Override protected int getLocalPlayerID() { return 0; }
}
