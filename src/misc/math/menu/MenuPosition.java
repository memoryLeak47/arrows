package misc.math.menu;

import misc.math.menu.MenuPoint;

public class MenuPosition extends MenuPoint
{
	public MenuPosition()
	{
		super();
	}

	public MenuPosition(int x, int y)
	{
		super(x, y);
	}

	public MenuPosition(MenuPoint point)
	{
		this(point.getX(), point.getY());
	}

	public boolean equals(MenuPosition position)
	{
		return (getX() == position.getX() && getY() == position.getY());
	}

	public void add(MenuPosition position)
	{
		setX(getX() + position.getX());
		setY(getY() + position.getY());
	}

	public void subtract(MenuPosition position)
	{
		setX(getX() - position.getX());
		setY(getY() - position.getY());
	}

	public MenuPosition plus(MenuPosition position)
	{
		return new MenuPosition(getX() + position.getX(), getY() + position.getY());
	}

	public MenuPosition minus(MenuPosition position)
	{
		return new MenuPosition(getX() - position.getX(), getY() - position.getY());
	}

	public boolean inRect(MenuPosition pos, MenuSize size)
	{
		return getX() >= pos.getX()
			&& getX() <= pos.getX() + size.getX()
			&& getY() >= pos.getY()
			&& getY() <= pos.getY() + size.getY();
	}

	public boolean inRect(MenuRect rect)
	{
		return inRect(rect.getPosition(), rect.getSize());
	}
}
