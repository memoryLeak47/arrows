package core.menu.menues;

import core.Main;
import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.*;
import misc.math.*;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		add(new Label(this, new Rect(400, 10, 200, 40), "Main Menu"));
		add(new EditField(this, new Rect(200, 200, 100, 100), "text"));
		add(new LinkButton(this, new Rect(300, 100, 100, 30), "Create Server", new CreateServerMenu()));
		add(new LinkButton(this, new Rect(300, 150, 100, 30), "Join Server", new JoinServerMenu()));
	}

	@Override public boolean isFullscreen() { return true; }

	

}
