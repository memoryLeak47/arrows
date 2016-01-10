package misc.math;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import game.Game;
import entity.Entity;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import misc.math.game.GameRect;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;
import misc.Debug;
import player.GamePlayer;

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
		return getPosition().minus(new GamePosition(Screen.WIDTH/TILESIZE/2, Screen.HEIGHT/TILESIZE/2)); // offset
	}

	public GameRect getRect()
	{
		return new GameRect(getPosition(), new GameSize(Screen.WIDTH/TILESIZE, Screen.HEIGHT/TILESIZE));
	}

	public PixelPosition gamePositionToPixelPosition(GameVector position)
	{
		Debug.warnIf(position == null, "Camera.gamePositionToPixelPosition(): position == null");

		GamePosition tmp = new GamePosition(position);
		tmp.subtract(getOffset());
		tmp.scale(TILESIZE);
		return new PixelPosition((int) tmp.getX(), (int) tmp.getY());
	}

	public PixelSize gameSizeToPixelSize(GameSize size)
	{
		Debug.warnIf(size == null, "Camera.gameSizeToPixelSize(): size == null");
		GameSize tmp = new GameSize(size);
		tmp.scale(TILESIZE);
		return new PixelSize((int) tmp.getX(), (int) tmp.getY());
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

		return new GameSize(((float) size.getX())/TILESIZE, ((float) size.getY())/TILESIZE);
	}

	public static Camera get()
	{
		Debug.warnIf(Game.get() == null, "Camera.get(): game == null");
		Debug.warnIf(Game.get().getCamera() == null, "Camera.get(): camera == null");
		return Game.get().getCamera();
	}

	public GamePosition getPosition()
	{
		return Game.get().getUncastedPlayers().get(localPlayerID).getPosition();
	}
}
