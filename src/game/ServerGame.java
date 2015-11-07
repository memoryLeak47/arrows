package game;

import java.util.LinkedList;

import game.tilemap.LobbyTileMap;
import game.player.ExtendedGamePlayer;
import game.player.ExtendedGamePlayerFrameUpdate;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.game.packets.EventPacket;
import network.game.packets.GameFrameUpdatePacket;

public class ServerGame extends Game
{
	private LinkedList<ExtendedGamePlayer> players;

	public ServerGame(LobbyTileMap lobbyMap, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		super(lobbyMap);
		players = new LinkedList<ExtendedGamePlayer>();
		for (LobbyPlayer player : lobbyPlayers)
		{
			players.add(new ExtendedGamePlayer(player));
		}
	}

	private ExtendedGamePlayerFrameUpdate getExtendedGamePlayerFrameUpdateByID(int id)
	{
		Debug.warn("ServerGame.getExtendedGamePlayerFrameUpdateByID(): return null TODO");
		return null;
		// TODO
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
	@Override public LinkedList<ExtendedGamePlayer> getPlayers()
	{
		Debug.warnIf(players == null, "ServerGame.getPlayers() return null");
		return players;
	}

	public GameFrameUpdatePacket getGameFrameUpdatePacketByID(int id)
	{
		Debug.warn("ServerGame.getGameFrameUpdatePacketByID(): return null; TODO");		
		return null;
	}
}
