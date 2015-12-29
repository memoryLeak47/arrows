package menu.menues;

import java.util.LinkedList;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import core.game.Game;
import entity.MinimizedEntity;
import menu.NetworkingMenu;
import misc.Debug;
import misc.game.Camera;
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

	@Override public void tick()
	{
		super.tick();
		if (getUncastedGame() != null)
		{
			getUncastedGame().tick();
		}
		else
		{
			Debug.warn("GameInterface.tick(): getUncastedGame() == null");
		}
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
		Screen.g().drawImage(getUncastedGame().getMapImage(), (int) - ((Camera.get().getOffset().getX() - 0.5f) * TILESIZE), (int) - ((Camera.get().getOffset().getY() - 0.5f) * TILESIZE), null);
		for (MinimizedEntity entity : getUncastedGame().getMinimizedEntities())
		{
			entity.render();
		}
	}
}
