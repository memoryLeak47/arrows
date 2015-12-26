package misc.math.menu;

import misc.math.menu.MenuPoint;

public class MenuSize extends MenuPoint
{
	public MenuSize()
	{
		super();
	}

	public MenuSize(int x, int y)
	{
		super(x, y);
	}

	public MenuSize(MenuPoint point)
	{
		this(point.getX(), point.getY());
	}
}
