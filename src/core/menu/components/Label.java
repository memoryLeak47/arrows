package core.menu.components;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class Label extends MenuComponent
{
	String caption;

	public Label(Menu menu, Rect rect, String caption)
	{
		super(menu, rect);
		this.caption = caption;
	}

	@Override
	public void render()
	{
		core.Screen.g().setColor(java.awt.Color.GREEN);
		core.Screen.g().fillRect(getPosition().getX(), getPosition().getY(), getSize().getX(), getSize().getY());
		core.Screen.g().setColor(java.awt.Color.BLACK);
		core.Screen.g().drawString(caption, getPosition().getX() + 1, getPosition().getY() + 12);
	}

}
