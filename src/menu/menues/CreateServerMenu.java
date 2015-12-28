package menu.menues;

import core.Main;
import menu.Menu;
import menu.components.*;
import misc.math.pixel.*;

public class CreateServerMenu extends Menu
{
	public CreateServerMenu()
	{
		getComponents().add(new Label(this, new PixelRect(400, 10, 200, 40), "Create Server")); // add Label "Create Server"
		getComponents().add(new Button(this, new PixelRect(300, 300, 100, 100), "Create Server") // add Button "Create Server"
		{
			@Override public void onClick(int mouseButton) // on click
			{
				Main.getMenues().add(new ServerLobbyMenu()); // add new ServerLobbyMenu
			}
		});
		getComponents().add(new BackButton(this, new PixelPosition(10, 500))); // add backbutton
	}
}
