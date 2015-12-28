package misc.math.pixel;

import misc.Debug;
import misc.math.pixel.PixelPoint;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;

public class PixelRect
{
	private PixelPosition position;
	private PixelSize size;

	public PixelRect(PixelPosition position, PixelSize size)
	{
		this.position = new PixelPosition(position);
		this.size = new PixelSize(size);
	}

	public PixelRect(PixelRect rect)
	{
		this(rect.getPosition(), rect.getSize());
	}

	public PixelRect(int x, int y, int w, int h)
	{
		this(new PixelPosition(x, y), new PixelSize(w, h));
	}

	public PixelRect()
	{
		this(new PixelPosition(0,0), new PixelSize(0,0));
	}

	public float distanceTo(PixelPoint point)
	{
		Debug.error("PixelRect.distanceTo(PixelPoint) not coded yet");
		// TODO
		return 2;
	}

	public void centerX(int width)
	{
		int left;
		left = (int)((width - this.getWidth()) / 2);
		setLeft(left);
	}

	public void centerY(int height)
	{
		int top;
		top = (int)((height - this.getHeight()) / 2);
		setTop(top);
	}

	// zentriert die Komponente im übergebenen PixelRectangle
	public void center(PixelRect rect)
	{
		centerX(rect);
		centerY(rect);
	}

	// zentriert die Komponente im übergebenen PixelRectangle in X-Richtung
	public void centerX(PixelRect rect)
	{
		int left;
		left = (int)((rect.getWidth() - this.getWidth()) / 2);
		setLeft(rect.getLeft() + left);
	}

	// zentriert die Komponente im übergebenen PixelRectangle in Y-Richtung
	public void centerY(PixelRect rect)
	{
		int top;
		top = (int)((rect.getHeight() - this.getHeight()) / 2);
		setTop(rect.getTop() + top);
	}

	public boolean equals(PixelRect rect)
	{
		return (getPosition().equals(rect.getPosition()) && getSize().equals(rect.getSize()));
	}

	public void setPosition(PixelPoint point) { position = new PixelPosition(point); }
	public void setPosition(int x, int y) { position = new PixelPosition(x, y); }
	public void setSize(PixelPoint point) { size = new PixelSize(point); }
	public void setSize(int x, int y) { size = new PixelSize(x, y); }
	public void setLeft(int left) { getPosition().setX(left); }
	public void setTop(int top) { getPosition().setX(top); }
	public void setWidth(int width) { getSize().setX(width); }
	public void setHeight(int height) { getSize().setY(height); }

	public final int getBot() { return (getY() + getHeight()); }
	public final int getLeft() { return getX(); }
	public final int getRight() { return (getX() + getWidth()); }
	public final int getTop() { return getY(); }
	public int getX() { return getPosition().getX(); }
	public int getY() { return getPosition().getY(); }
	public int getWidth() { return getSize().getX(); }
	public int getHeight() { return getSize().getY(); }
	public PixelSize getSize() { return size; }
	public PixelPosition getPosition() { return position; }
}
