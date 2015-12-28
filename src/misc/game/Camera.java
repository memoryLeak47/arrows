package misc.game;

import static core.Main.INGAME_SCREENSIZE_X;
import static core.Main.INGAME_SCREENSIZE_Y;
import static core.Main.TILESIZE;
import core.Main;
import entity.Entity;
import misc.math.game.GamePoint;
import misc.math.game.GamePosition;
import misc.math.game.GameRect;
import misc.math.game.GameSize;
import misc.math.menu.MenuPosition;
import misc.math.menu.MenuSize;
import misc.Debug;
import network.game.player.GamePlayer;

public class Camera
{
	// the middle of the camera
	private int localPlayerID;

	public Camera(int localPlayerID)
	{
		this.localPlayerID = localPlayerID;
	}

	public GamePoint getOffset()
	{
		GamePlayer gp = Main.getGame().getUncastedPlayers().get(localPlayerID);
		return gp.getPosition() // player-pos
			.plus(gp.getSize().times(0.5f)) // player-center
			.minus(new GamePosition(INGAME_SCREENSIZE_X/2, INGAME_SCREENSIZE_Y/2)); // offset
	}

	public GameRect getRect()
	{
		return new GameRect(getOffset(), new GameSize(INGAME_SCREENSIZE_X, INGAME_SCREENSIZE_Y));
	}

	public MenuPosition gamePositionToScreenPosition(GamePosition position)
	{
		Debug.warnIf(position == null, "Camera.gamePositionToScreenPosition(): position == null");

		position.subtract(getOffset());
		position.scale(TILESIZE);
		return new MenuPosition((int) position.getX(), (int) position.getY());
	}

	public MenuSize gameSizeToScreenSize(GameSize size)
	{
		Debug.warnIf(size == null, "Camera.gameSizeToScreenSize(): size == null");

		size.scale(TILESIZE);
		return new MenuSize((int) size.getX(), (int) size.getY());
	}
}
