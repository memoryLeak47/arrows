package core.menu.components;

import core.Main;
import core.Screen;
import core.menu.ComponentContainer;
import core.menu.components.Button;
import misc.math.*;

public class QuitButton extends Button
{
	public QuitButton(ComponentContainer parent, Position position)
	{
		super(parent, new Rect(position, new Size(100, 50)), "Quit"); // button constructor
	}

	public QuitButton(ComponentContainer parent, Rect rect)
	{
		super(parent, rect, "Quit"); // button constructor
	}

	@Override public void onClick(int button) // when button is pressed
	{
		Main.quit();
	}

}
