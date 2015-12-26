package misc.math.menu;

import misc.Debug;
import misc.math.menu.MenuPoint;
import misc.math.menu.MenuPosition;
import misc.math.menu.MenuSize;

public class MenuRect
{
	private MenuPosition position;
	private MenuSize size;

	public MenuRect(MenuPosition position, MenuSize size)
	{
		this.position = new MenuPosition(position);
		this.size = new MenuSize(size);
	}

	public MenuRect(MenuRect rect)
	{
		this(rect.getPosition(), rect.getSize());
	}

	public MenuRect(int x, int y, int w, int h)
	{
		this(new MenuPosition(x, y), new MenuSize(w, h));
	}

	public MenuRect()
	{
		this(new MenuPosition(0,0), new MenuSize(0,0));
	}

	public float distanceTo(MenuPoint point)
	{
		Debug.error("MenuRect.distanceTo(MenuPoint) not coded yet");
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

	// zentriert die Komponente im übergebenen MenuRectangle
	public void center(MenuRect rect)
	{
		centerX(rect);
		centerY(rect);
	}

	// zentriert die Komponente im übergebenen MenuRectangle in X-Richtung
	public void centerX(MenuRect rect)
	{
		int left;
		left = (int)((rect.getWidth() - this.getWidth()) / 2);
		setLeft(rect.getLeft() + left);
	}

	// zentriert die Komponente im übergebenen MenuRectangle in Y-Richtung
	public void centerY(MenuRect rect)
	{
		int top;
		top = (int)((rect.getHeight() - this.getHeight()) / 2);
		setTop(rect.getTop() + top);
	}

	public boolean equals(MenuRect rect)
	{
		return (getPosition().equals(rect.getPosition()) && getSize().equals(rect.getSize()));
	}

	public void setPosition(MenuPoint point) { position = new MenuPosition(point); }
	public void setPosition(int x, int y) { position = new MenuPosition(x, y); }
	public void setSize(MenuPoint point) { size = new MenuSize(point); }
	public void setSize(int x, int y) { size = new MenuSize(x, y); }
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
	public MenuSize getSize() { return size; }
	public MenuPosition getPosition() { return position; }
}
