package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.ComponentContainer;
import misc.math.Rect;

public class Button extends MenuComponent
{
	private String caption;
	
	public Button(ComponentContainer parent, Rect rect, String caption)
	{
		super(parent, rect); // setup menu which contains this Button and the rect of the button
		this.caption = caption; // set caption
	}

	@Override public void render() // draws content on getGraphics() -> on image
	{
		Screen.g().setColor(Color.RED); // sets graphics color to red
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // fill rect of the button
		Screen.g().setColor(Color.BLACK); // set color to black
		Screen.g().drawString(caption, getOffset().getX() + 1, getOffset().getY() + 12); // write caption on the rect
	}
}
