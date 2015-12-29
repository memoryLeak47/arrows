package misc.math.game;

import core.Main;
import misc.math.game.GamePoint;
import misc.math.pixel.PixelSize;
import misc.game.Camera;
import graphics.ImageFile;
import graphics.ImageID;

public class GameSize extends GamePoint
{
	public GameSize()
	{
		super();
	}

	public GameSize(float x, float y)
	{
		super(x, y);
	}

	public GameSize(GamePoint point)
	{
		this(point.getX(), point.getY());
	}

	public GameSize(ImageID id)
	{
		this(Main.getGame().getCamera().pixelSizeToGameSize(new PixelSize(id)));
	}
}
