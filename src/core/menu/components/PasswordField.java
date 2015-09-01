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

	@Override public void render() // TODO make prettier
	{
		Screen.g().setColor(Color.BLUE); // set color to blue
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // fill rect
		Screen.g().setColor(Color.BLACK); // set color to black
		Screen.g().drawString(getDotString(), getOffset().getX() + 1, getOffset().getY() + 12); // draw text in rect
	}

	private String getDotString()
	{
		String dotString = "";
		for (int i = 0; i < getText().length(); i++)
		{
			dotString += ".";
		}
		return dotString;
	}
}
