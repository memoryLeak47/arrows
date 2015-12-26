package menu.components;

import core.Main;
import menu.ComponentContainer;
import menu.components.Button;
import misc.math.menu.*;

public class BackButton extends Button
{
	public BackButton(ComponentContainer parent, MenuPosition position)
	{
		super(parent, new MenuRect(position, new MenuSize(100, 50)), "Back"); // button constructor
	}

	public BackButton(ComponentContainer parent, MenuRect rect)
	{
		super(parent, rect, "Back"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.getMenues().remove(Main.getMenues().size()-1); // remove last menu
	}

}
