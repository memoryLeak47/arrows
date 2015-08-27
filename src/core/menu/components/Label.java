package core.menu.components;

import java.awt.Color;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class Label extends MenuComponent
{
	private String caption;

	public Label(Menu menu, Rect rect, String caption)
	{
		super(menu, rect); // setup menu and rect
		this.caption = caption; // set caption
		updateImage(); // setup image
	}

	@Override public void updateImage() // TODO make prettier
	{
		getGraphics().setColor(Color.GREEN); // sets color to green
		getGraphics().fillRect(0, 0, getWidth(), getHeight()); // fills rect with green
		getGraphics().setColor(Color.BLACK); // sets color to black
		getGraphics().drawString(caption, 1, 12); // draws the string with black
	}

}
