package core.menu.menues;

import core.Main;
import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.*;
import misc.Debug;
import misc.math.*;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		getComponents().add(new Label(this, new Rect(400, 10, 200, 40), "Main Menu"));
		getComponents().add(new EditField(this, new Rect(200, 200, 100, 100), "text"));
		getComponents().add(new Button(this, new Rect(300, 100, 100, 30), "Create Server")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().add(new CreateServerMenu());
			}
		});
		getComponents().add(new Button(this, new Rect(300, 150, 100, 30), "Join Server")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().add(new JoinServerMenu());
			}
		});
		getComponents().add(new Button(this, new Rect(140, 500, 100, 30), "Logout")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().remove(Main.getMenues().getLast());
			}
		});
		getComponents().add(new QuitButton(this, new Rect(20, 500, 100, 30)));
	}

}
