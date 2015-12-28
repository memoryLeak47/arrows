package misc.game;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import entity.Entity;
import misc.math.game.GamePoint;
import misc.math.game.GamePosition;
import misc.math.game.GameRect;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;
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
			.minus(new GamePosition(Screen.WIDTH/TILESIZE/2, Screen.HEIGHT/TILESIZE/2)); // offset
	}

	public GameRect getRect()
	{
		return new GameRect(getOffset(), new GameSize(Screen.WIDTH/TILESIZE, Screen.HEIGHT/TILESIZE));
	}

	public PixelPosition gamePositionToScreenPosition(GamePosition position)
	{
		Debug.warnIf(position == null, "Camera.gamePositionToScreenPosition(): position == null");

		position.subtract(getOffset());
		position.scale(TILESIZE);
		return new PixelPosition((int) position.getX(), (int) position.getY());
	}

	public PixelSize gameSizeToScreenSize(GameSize size)
	{
		Debug.warnIf(size == null, "Camera.gameSizeToScreenSize(): size == null");

		size.scale(TILESIZE);
		return new PixelSize((int) size.getX(), (int) size.getY());
	}
}
