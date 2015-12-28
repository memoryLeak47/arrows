package misc.math.game;

import misc.math.game.GamePoint;
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
		setX(ImageFile.getImageByImageID(id).getWidth());
		setY(ImageFile.getImageByImageID(id).getHeight());
	}
}
