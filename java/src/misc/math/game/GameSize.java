package misc.math.game;

import core.Main;
import misc.compress.*;
import misc.math.game.GameVector;
import misc.math.pixel.PixelSize;
import misc.math.Camera;
import graphics.ImageFile;
import graphics.ImageID;

public class GameSize extends GameVector
{
	public GameSize()
	{
		super();
	}

	public GameSize(float x, float y)
	{
		super(x, y);
	}

	public GameSize(GameVector point)
	{
		this(point.getX(), point.getY());
	}

	public GameSize(ImageID id)
	{
		this(Camera.get().pixelSizeToGameSize(new PixelSize(id)));
	}

	public GameSize(CompressBuffer buffer)
	{
		super(buffer);
	}

	@Override public byte getCID() { return Compressor.GAME_SIZE_CID; }

	public GameSize timesX(float s)
	{
		return new GameSize(super.timesX(s));
	}

	public GameSize timesY(float s)
	{
		return new GameSize(super.timesY(s));
	}

	public GameSize plus(GameVector size)
	{
		return new GameSize(super.plus(size));
	}

	public GameSize plusX(float f)
	{
		return new GameSize(super.plusX(f));
	}

	public GameSize plusY(float f)
	{
		return new GameSize(super.plusY(f));
	}

	public GameSize minus(GameVector size)
	{
		return new GameSize(super.minus(size));
	}

	public GameSize times(float s)
	{
		return new GameSize(super.times(s));
	}

	public GameSize divide(float s)
	{
		return new GameSize(super.divide(s));
	}
}
