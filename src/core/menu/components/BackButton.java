package core.menu.components;

import core.Main;
import core.menu.Menu;
import core.menu.components.Button;
import misc.math.*;

public class BackButton extends Button
{
	public BackButton(Menu menu, Position position)
	{
		super(menu, new Rect(position, new Size(100, 50)), "Back"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.getMenues().remove(Main.getMenues().size()-1); // remove last menu
	}

}
