package misc.math.pixel;

import misc.math.pixel.PixelPoint;
import graphics.ImageFile;
import graphics.ImageID;

public class PixelSize extends PixelPoint
{
	public PixelSize()
	{
		super();
	}

	public PixelSize(int x, int y)
	{
		super(x, y);
	}

	public PixelSize(PixelPoint point)
	{
		this(point.getX(), point.getY());
	}

	public PixelSize(ImageID id)
	{
		setX(ImageFile.getImageByImageID(id).getWidth());
		setY(ImageFile.getImageByImageID(id).getHeight());
	}
}
