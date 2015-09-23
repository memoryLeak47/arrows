package menu.components;

import core.Main;
import menu.ComponentContainer;
import menu.components.Button;
import misc.math.*;

public class BackButton extends Button
{
	public BackButton(ComponentContainer parent, Position position)
	{
		super(parent, new Rect(position, new Size(100, 50)), "Back"); // button constructor
	}

	public BackButton(ComponentContainer parent, Rect rect)
	{
		super(parent, rect, "Back"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.getMenues().remove(Main.getMenues().size()-1); // remove last menu
	}

}
