package core.menu.menues;

import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.*;
import misc.math.*;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		add(new EditField(this, new Rect(200, 200, 100, 100), "text"));
		add(new Button(this, new Rect(10, 10, 30, 30), "caption")
		{
			@Override
			public void onClick(int mouseButton)
			{
				System.out.println("Button clicked");
			}
		});
	}

	@Override
	public boolean isFullscreen() { return true; }

	

}
