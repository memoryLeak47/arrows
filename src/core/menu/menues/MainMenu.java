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
		add(new Button(this, new Rect(10, 10, 100, 30), "Create Server")
		{
			@Override
			public void onClick(int mouseButton)
			{
				Main.getMenues().add(new CreateServerMenu());
			}
		});
	}

	@Override
	public boolean isFullscreen() { return true; }

	

}
