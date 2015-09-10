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
		super(parent, rect);
		this.caption = caption;
	}

	@Override public void render()
	{
		Screen.g().setColor(Color.GREEN);
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		Screen.g().setColor(Color.BLACK);
		Screen.g().drawString(caption, getOffset().getX() + 1, getOffset().getY() + 12);
	}

}
