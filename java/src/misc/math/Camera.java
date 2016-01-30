package misc.math;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import game.Game;
import entity.Entity;
import misc.math.collision.BorderRect;
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
	public static final int MOUSE_MOVE_BORDER_TOLERANCE = 4;
	public static final int MOUSE_MOVE_BORDER_SPEED = 1;

	// the middle of the camera
	private GamePosition position = new GamePosition();
	private int localPlayerID;
	private boolean playerFocused = true;

	public Camera(int localPlayerID)
	{
		this.localPlayerID = localPlayerID;
	}

	public void tick()
	{
		PixelPosition cursor = Screen.getCursorPosition();
		Debug.warnIf(cursor == null, "Camera.tick(): cursor is null");

		if (!isPlayerFocused())
		{
			// TODO remove when fullscreen works
			if ((cursor.getX() == -1 && cursor.getY() == -1)) // if mouse out of screen
			{
				position = position.plusY(-MOUSE_MOVE_BORDER_SPEED); // mouse is probably at the top
			}
			else
			{
				if (Screen.WIDTH - cursor.getX() < MOUSE_MOVE_BORDER_TOLERANCE)
				{
					position = position.plusX(MOUSE_MOVE_BORDER_SPEED);
				}
				else if (cursor.getX() < MOUSE_MOVE_BORDER_TOLERANCE)
				{
					position = position.plusX(-MOUSE_MOVE_BORDER_SPEED);
				}

				if (Screen.HEIGHT - cursor.getY() - 40 /*TODO remove when fullscreen works */  < MOUSE_MOVE_BORDER_TOLERANCE)
				{
					position = position.plusY(MOUSE_MOVE_BORDER_SPEED);
				}
				else if (cursor.getY() < MOUSE_MOVE_BORDER_TOLERANCE)
				{
					position = position.plusY(-MOUSE_MOVE_BORDER_SPEED);
				}
			}
		}
	}

	public void keyPressed(int keyID)
	{
		switch (keyID)
		{
			case 0:
			{
				break;
			}
			case 1:
			{
				playerFocused = true;
				break;
			}
		}
	}

	public void keyReleased(int keyID)
	{
		switch (keyID)
		{
			case 0:
			{
				playerFocused = false;
				centerPlayer();
				break;
			}
			case 1:
			{
				break;
			}
		}
	}

	public void centerPlayer()
	{
		if (Game.get().getUncastedPlayers().get(localPlayerID) != null)
			position = new GamePosition(Game.get().getUncastedPlayers().get(localPlayerID).getPosition());
	}

	public GameVector getOffset()
	{
		return getPosition().minus(new GamePosition(Screen.WIDTH/TILESIZE/2, Screen.HEIGHT/TILESIZE/2)); // offset
	}

	public BorderRect getRect()
	{
		return new BorderRect(getPosition(), new GameSize(Screen.WIDTH/TILESIZE, Screen.HEIGHT/TILESIZE));
	}

	public PixelPosition gamePositionToPixelPosition(GameVector position)
	{
		Debug.warnIf(position == null, "Camera.gamePositionToPixelPosition(): position == null");

		GameVector tmp = new GameVector(position).minus(getOffset()).times(TILESIZE);
		return new PixelPosition((int) tmp.getX(), (int) tmp.getY());
	}

	public PixelSize gameSizeToPixelSize(GameSize size)
	{
		Debug.warnIf(size == null, "Camera.gameSizeToPixelSize(): size == null");
		GameSize tmp = new GameSize(size).times(TILESIZE);
		return new PixelSize((int) tmp.getX(), (int) tmp.getY());
	}

	public GamePosition pixelPositionToGamePosition(PixelPosition position)
	{
		Debug.warnIf(position == null, "Camera.pixelPositionToGamePosition(): position == null");

		GamePosition tmp = new GamePosition(position.getX(), position.getY()).divide(TILESIZE).plus(getOffset());
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
		if (isPlayerFocused())
			centerPlayer();
		return position;
	}

	public boolean isPlayerFocused()
	{
		return playerFocused;
	}
}
