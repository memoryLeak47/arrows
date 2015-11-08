package menu.menues;

import java.util.LinkedList;

import core.Main;
import core.game.Game;
import tilemap.LobbyTileMap;
import menu.NetworkingMenu;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.Packet;

public abstract class GameInterface extends NetworkingMenu
{
	private Game game;

	public GameInterface(Game game)
	{
		setGame(game);
	}

	private void setGame(Game game)
	{
		if (game == null)
			Debug.warn("GameInterface.setGame(null)");
		this.game = game;
	}

	protected Game getUncastedGame() { return game; }

}
