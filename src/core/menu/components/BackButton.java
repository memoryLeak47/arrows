package core.menu.components;

import core.Main;
import core.menu.components.Button;
import core.menu.Menu;
import misc.math.*;

public class BackButton extends Button
{
	public BackButton(Menu menu, Position position)
	{
		super(menu, new Rect(position, new Size(100, 50)), "Back");
	}

	@Override public void onClick(int button)
	{
		Main.getMenues().remove(Main.getMenues().size()-1);
	}

}
