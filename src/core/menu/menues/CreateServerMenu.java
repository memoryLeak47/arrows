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
		add(new EditField(this, new Rect(10, 10, 10, 10), "Enter Map path"));
		add(new BackButton(this, new Position(10, 500)));
	}

	@Override
	public boolean isFullscreen() { return true; }
}
