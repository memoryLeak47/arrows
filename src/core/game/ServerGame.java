package core.game;

import java.util.LinkedList;

import entity.entities.bullet.ExtendedBullet;
import entity.entities.bullet.MinimizedBullet;
import tilemap.LobbyTileMap;
import network.game.player.GamePlayer;
import network.game.player.ServerGamePlayer;
import network.game.player.LocalClientGamePlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import misc.Debug;
import misc.math.Position;
import misc.game.effect.Effect;
import misc.game.effect.MinimizedEffect;
import network.lobby.LobbyPlayer;
import network.game.packets.EventPacket;
import network.game.packets.GameFrameUpdatePacket;

public class ServerGame extends Game
{
	private LinkedList<ServerGamePlayer> players = new LinkedList<ServerGamePlayer>();
	private LinkedList<ExtendedBullet> bullets = new LinkedList<ExtendedBullet>();

	public ServerGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(lobbyMap);
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new ServerGamePlayer(player, new Position(0, 0))); // TODO useful position
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
	
	// Muss die "ExtendedBullets" in "MinimizedBullets" ändern
	@Override LinkedList<MinimizedBullet> getBullets()
	{
		Debug.warn("ServerGame.getBullets(): TODO)");
		return null;
	}

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
		Debug.warnIf(players == null, "ServertGame.getPlayers(): return null");
		return players;
	}

	public GameFrameUpdatePacket getGameFrameUpdatePacketByID(int id)
	{
		Debug.warn("ServerGame.getGameFrameUpdatePacketByID(): return null; TODO");		
		return null;
	}
}
