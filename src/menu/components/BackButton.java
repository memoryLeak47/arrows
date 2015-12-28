package menu.components;

import core.Main;
import menu.ComponentContainer;
import menu.components.Button;
import misc.math.pixel.*;

public class BackButton extends Button
{
	public BackButton(ComponentContainer parent, PixelPosition position)
	{
		super(parent, new PixelRect(position, new PixelSize(100, 50)), "Back"); // button constructor
	}

	public BackButton(ComponentContainer parent, PixelRect rect)
	{
		super(parent, rect, "Back"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.getMenues().remove(Main.getMenues().size()-1); // remove last menu
	}

}
