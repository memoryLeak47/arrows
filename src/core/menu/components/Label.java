package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.ComponentContainer;
import misc.math.Rect;

public class Label extends MenuComponent
{
	private String caption;

	public Label(ComponentContainer parent, Rect rect, String caption)
	{
		super(parent, rect); // setup menu and rect
		this.caption = caption; // set caption
	}

	@Override public void render() // TODO make prettier
	{
		Screen.g().setColor(Color.GREEN); // sets color to green
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // fills rect with green
		Screen.g().setColor(Color.BLACK); // sets color to black
		Screen.g().drawString(caption, getOffset().getX() + 1, getOffset().getY() + 12); // draws the string with black
	}

}
