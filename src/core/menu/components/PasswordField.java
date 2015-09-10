package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.ComponentContainer;
import misc.math.Rect;

public class PasswordField extends EditField
{
	public PasswordField(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	@Override public void render()
	{
		Screen.g().setColor(Color.BLUE);
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		Screen.g().setColor(Color.BLACK);
		Screen.g().drawString(getDotString(), getOffset().getX() + 1, getOffset().getY() + 12);
	}

	private String getDotString()
	{
		String dotString = "";
		for (int i = 0; i < getText().length(); i++)
		{
			dotString += "*";
		}
		return dotString;
	}
}
