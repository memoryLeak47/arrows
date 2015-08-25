package core.menu.menues;

import core.Main;
import core.menu.Menu;
import core.menu.components.*;
import misc.math.*;

public class JoinServerMenu extends Menu
{
	public JoinServerMenu()
	{
		add(new Label(this, new Rect(400, 10, 200, 40), "Join Server"));
		add(new BackButton(this, new Position(10, 500)));
	}

	@Override public boolean isFullscreen() { return true; }
}
