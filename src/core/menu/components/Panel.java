package core.menu.components;

import java.awt.Color;

import core.menu.components.ComponentContainer;
import core.menu.Menu;
import misc.math.Rect;

public class Panel extends ComponentContainer
{
	public Panel(Menu menu, Rect rect)
	{
		super(menu, rect);
		updateImage();
	}

	@Override public void updateImage()
	{
		super.updateImage(); // draw content of all components
		getGraphics().setColor(Color.BLUE); // set color to blue
		getGraphics().drawRect(0, 0, getWidth()-1, getHeight()-1); // draw border
	}
}
