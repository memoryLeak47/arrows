package core.game;

import java.util.LinkedList;

import entity.entities.bullet.MinimizedBullet;
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
	private LinkedList<MinimizedBullet> bullets;
	private LocalClientGamePlayerFrameUpdate localPlayerUpdate;

	private final int localPlayerID;

	public ClientGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID)
	{
		super(lobbyMap);
		this.localPlayerID = localPlayerID;

		players = new LinkedList<ClientGamePlayer>();
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new ClientGamePlayer(player));
		}
	}

	public void apply(GameFrameUpdatePacket updatePacket)
	{
		Debug.warn("ClientGame.update(): TODO"); // TODO
	}

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

	@Override LinkedList<MinimizedBullet> getBullets()
	{
		Debug.warnIf(bullets == null, "ClientGame.getBullets(): return null");
		return bullets;
	}
}
