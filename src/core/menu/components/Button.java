package core.menu.components;

import java.awt.Color;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class Button extends MenuComponent
{
	private String caption;
	
	public Button(Menu menu, Rect rect, String caption)
	{
		super(menu, rect); // setup menu which contains this Button and the rect of the button
		this.caption = caption; // set caption
		updateImage(); // setup image
	}

	@Override public void updateImage() // draws content on getGraphics() -> on image
	{
		getGraphics().setColor(Color.RED); // sets graphics color to red
		getGraphics().fillRect(0, 0, getWidth(), getHeight()); // fill rect of the button
		getGraphics().setColor(Color.BLACK); // set color to black
		getGraphics().drawString(caption, 1, 12); // write caption on the rect
	}
}
