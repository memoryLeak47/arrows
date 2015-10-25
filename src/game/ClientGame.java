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
		this.localPlayerID = localPlayerID;
	}

	// TODO

	public void apply(GameFrameUpdatePacket updatePacket)
	{
		Debug.warn("ClientGame.update(): TODO");
	}
}
