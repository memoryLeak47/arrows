package core.menu.menues;

import core.Main;
import core.menu.Menu;
import core.menu.components.*;
import misc.math.*;

public class CreateServerMenu extends Menu
{
	public CreateServerMenu()
	{
		add(new Label(this, new Rect(400, 10, 200, 40), "Create Server"));
		add(new LinkButton(this, new Rect(300, 300, 100, 100), "Create Server", new ServerLobbyMenu()));
		add(new BackButton(this, new Position(10, 500)));
	}

	@Override public boolean isFullscreen() { return true; }
}
