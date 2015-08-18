package core.menu.menues;

import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.Button;
import misc.math.*;
import network.sendable.events.MouseButton;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		add(new Button(this, new Rect(new Position(10, 10), new Size(30, 30)), "caption")
		{
			@Override
			public void onClick(MouseButton mouseButton)
			{
				System.out.println("Button clicked");
			}
		});
	}

	@Override
	public boolean isFullscreen() { return true; }

	

}
