package core.menu.components;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class EditField extends MenuComponent
{
	private String text;

	public EditField(Menu menu, Rect rect, String text)
	{
		super(menu, rect);
		this.text = text;
		updateImage();
	}

	@Override public void onKeyPress(char key)
	{	
		if (((int) key) == 8)
		{
			if (text.length() <= 0)
			{
				return;
			}
			text = text.substring(0,text.length()-1);
		}

		if (!misc.KeyChecker.isSign(key))
		{
			return;
		}
		else
		{
			text += key;
		}
	}

	@Override public void updateImage()
	{
		getGraphics().setColor(java.awt.Color.BLUE);
		getGraphics().fillRect(0, 0, getSize().getX(), getSize().getY());
		getGraphics().setColor(java.awt.Color.BLACK);
		getGraphics().drawString(text, 1, 12);
	}

}
