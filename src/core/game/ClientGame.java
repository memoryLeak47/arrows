package core.game;

import java.util.LinkedList;

import entity.bullet.MinimizedBullet;
import entity.player.MinimizedGamePlayer;
import entity.player.ExtendedGamePlayerFrameUpdate;
import tilemap.LobbyTileMap;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.game.packets.GameFrameUpdatePacket;

public class ClientGame extends Game
{
	private LinkedList<MinimizedGamePlayer> players;
	private LinkedList<MinimizedBullet> bullets;
	private ExtendedGamePlayerFrameUpdate localPlayerUpdate;

	private final int localPlayerID;

	public ClientGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID)
	{
		super(lobbyMap);
		this.localPlayerID = localPlayerID;

		players = new LinkedList<MinimizedGamePlayer>();
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new MinimizedGamePlayer(player));
		}
	}

	public void apply(GameFrameUpdatePacket updatePacket)
	{
		// TODO
		Debug.warn("ClientGame.update(): TODO");
	}

	@Override public LinkedList<MinimizedGamePlayer> getPlayers()
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
