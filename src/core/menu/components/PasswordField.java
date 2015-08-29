package core.menu.components;

import java.awt.Color;

import core.menu.Menu;
import misc.math.Rect;

public class PasswordField extends EditField
{
	public PasswordField(Menu menu, Rect rect)
	{
		super(menu, rect);
	}

	@Override public void updateImage() // TODO make prettier
	{
		getGraphics().setColor(Color.BLUE); // set color to blue
		getGraphics().fillRect(0, 0, getWidth(), getHeight()); // fill rect
		getGraphics().setColor(Color.BLACK); // set color to black
		getGraphics().drawString(getDotString(), 1, 12); // draw text in rect
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
