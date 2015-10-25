package game;

import java.util.LinkedList;

import game.tilemap.LobbyTileMap;
import game.player.ExtendedGamePlayer;
import game.player.ExtendedGamePlayerFrameUpdate;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.game.packets.EventPacket;

public class ServerGame extends Game
{
	private LinkedList<ExtendedGamePlayer> players;

	public ServerGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		Debug.warn("ServerGame.<init>(): TODO");
	}

	public void handleEvent(EventPacket event, int id)
	{
		Debug.warn("ServerGame.handleEvent(): TODO");		
	}

	public void tick()
	{
		Debug.warn("ServerGame.tick(): TODO");		
	}

	public ExtendedGamePlayerFrameUpdate getExtendedGamePlayerFrameUpdate(int id)
	{
		Debug.warn("ServerGame.getExtendedGamePlayerFrameUpdate(): TODO");		
		return null;
	}
}
