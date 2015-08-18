package core.menu.components;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class Button extends MenuComponent
{
	public Button(Menu menu, Rect rect)
	{
		super(menu, rect);
		System.out.println("Button created");
	}

	public void render()
	{
		core.Screen.g().setColor(java.awt.Color.RED);
		core.Screen.g().fillRect(getPosition().getX(), getPosition().getY(), getSize().getX(), getSize().getY());
	}
}
