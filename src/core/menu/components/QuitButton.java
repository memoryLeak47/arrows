package core.menu.components;

import core.Main;
import core.menu.Menu;
import core.menu.components.Button;
import misc.math.*;

public class QuitButton extends Button
{
	public QuitButton(Menu menu, Position position)
	{
		super(menu, new Rect(position, new Size(100, 50)), "Quit"); // button constructor
	}

	public QuitButton(Menu menu, Rect rect)
	{
		super(menu, rect, "Quit"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.quit();
	}

}
