package misc.math.game;

import core.Main;
import misc.compress.Compressor;
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

	@Override public byte getCID() { return Compressor.GAME_SIZE_CID; }
}
