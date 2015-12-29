package misc.game;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import core.game.Game;
import entity.Entity;
import misc.math.game.GameVector;
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

	public GameVector getOffset()
	{
		GamePlayer gp = Game.get().getUncastedPlayers().get(localPlayerID);
		return gp.getPosition() // player-pos
			.plus(gp.getSize().times(0.5f)) // player-center
			.minus(new GamePosition(Screen.WIDTH/TILESIZE/2, Screen.HEIGHT/TILESIZE/2)); // offset
	}

	public GameRect getRect()
	{
		return new GameRect(getOffset(), new GameSize(Screen.WIDTH/TILESIZE, Screen.HEIGHT/TILESIZE));
	}

	public PixelPosition gamePositionToPixelPosition(GamePosition position)
	{
		Debug.warnIf(position == null, "Camera.gamePositionToPixelPosition(): position == null");

		position.subtract(getOffset());
		position.scale(TILESIZE);
		return new PixelPosition((int) position.getX(), (int) position.getY());
	}

	public PixelSize gameSizeToPixelSize(GameSize size)
	{
		Debug.warnIf(size == null, "Camera.gameSizeToPixelSize(): size == null");

		size.scale(TILESIZE);
		return new PixelSize((int) size.getX(), (int) size.getY());
	}

	public GamePosition pixelPositionToGamePosition(PixelPosition position)
	{
		Debug.warnIf(position == null, "Camera.pixelPositionToGamePosition(): position == null");

		GamePosition tmp = new GamePosition(position.getX(), position.getY());
		tmp.divide(TILESIZE);
		tmp.add(getOffset());
		return tmp;
	}

	public GameSize pixelSizeToGameSize(PixelSize size)
	{
		Debug.warnIf(size == null, "Camera.pixelSizeToGameSize(): size == null");

		return new GameSize(size.getX()/TILESIZE, size.getY()/TILESIZE);
	}

	public static Camera get()
	{
		Debug.warnIf(Game.get() == null, "Camera.get(): game == null");
		Debug.warnIf(Game.get().getCamera() == null, "Camera.get(): camera == null");
		return Game.get().getCamera();
	}
}
