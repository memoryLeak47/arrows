package core.menu.menues;

import core.menu.Menu;
import core.menu.components.*;
import misc.math.Rect;

public class CreateServerMenu extends Menu
{
	public CreateServerMenu()
	{
		add(new Label(this, new Rect(400, 10, 200, 40), "Create Server"));
	}

	@Override
	public boolean isFullscreen() { return true; }
}
