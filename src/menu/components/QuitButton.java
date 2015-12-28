package menu.components;

import core.Main;
import core.Screen;
import menu.ComponentContainer;
import menu.components.Button;
import misc.math.pixel.*;

public class QuitButton extends Button
{
	public QuitButton(ComponentContainer parent, PixelPosition position)
	{
		super(parent, new PixelRect(position, new PixelSize(100, 50)), "Quit");
	}

	public QuitButton(ComponentContainer parent, PixelRect rect)
	{
		super(parent, rect, "Quit");
	}

	@Override public void onClick(int button)
	{
		Main.quit();
	}

}
