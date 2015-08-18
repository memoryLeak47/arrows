package core.menu.menues;

import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.Button;
import misc.math.*;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		add(new Button(this, new Rect(new Position(10, 10), new Size(30, 30))));
	}

	@Override
	public boolean isFullscreen() { return true; }

	

}
