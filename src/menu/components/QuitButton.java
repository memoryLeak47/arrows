package menu.components;

import core.Main;
import core.Screen;
import menu.ComponentContainer;
import menu.components.Button;
import misc.math.menu.*;

public class QuitButton extends Button
{
	public QuitButton(ComponentContainer parent, MenuPosition position)
	{
		super(parent, new MenuRect(position, new MenuSize(100, 50)), "Quit");
	}

	public QuitButton(ComponentContainer parent, MenuRect rect)
	{
		super(parent, rect, "Quit");
	}

	@Override public void onClick(int button)
	{
		Main.quit();
	}

}
