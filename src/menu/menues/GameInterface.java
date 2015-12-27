package menu.menues;

import java.util.LinkedList;

import core.Main;
import core.game.Game;
import entity.MinimizedEntity;
import menu.NetworkingMenu;
import misc.Debug;
import network.lobby.LobbyPlayer;
import network.Packet;
import tilemap.LobbyTileMap;

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

	@Override public void render()
	{
		Debug.warn("GameInterface.render(): Hier muss noch das Bild schwarz übermalt werden");
		for (MinimizedEntity entity : getUncastedGame().getMinimizedEntities())
		{
			entity.render();
		}
	}
}
