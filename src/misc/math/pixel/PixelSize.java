package misc.math.pixel;

import misc.math.pixel.PixelPoint;

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
}
