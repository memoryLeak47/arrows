package game;

import java.util.LinkedList;

import game.tilemap.LobbyTileMap;
import game.player.MinimizedGamePlayer;
import game.player.ExtendedGamePlayerFrameUpdate;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.game.packets.GameFrameUpdatePacket;

public class ClientGame extends Game
{
	private LinkedList<MinimizedGamePlayer> players;
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
}
