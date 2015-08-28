package core.menu.components;

import java.awt.Color;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class EditField extends MenuComponent
{
	private String text;

	public EditField(Menu menu, Rect rect, String text)
	{
		super(menu, rect);
		this.text = text; // set text
		updateImage(); // create image
	}

	public EditField(Menu menu, Rect rect)
	{
		this(menu, rect, "");
	}

	@Override public void onKeyPress(char key)
	{	
		if (((int) key) == 8) // if backspace is pressed
		{
			if (text.length() <= 0) // if text still contains letters (not all letters are removed)
			{
				return; // return, because backspace has no function then
			}
			text = text.substring(0,text.length()-1); // remove last letter
			updateImage();
		}

		if (!misc.KeyChecker.isSign(key)) // if the key is not a valid sign
		{
			return; // return 
		}
		else // else
		{
			text += key; // add it to text
			updateImage();
		}
	}

	@Override public void updateImage() // TODO make prettier
	{
		getGraphics().setColor(Color.BLUE); // set color to blue
		getGraphics().fillRect(0, 0, getWidth(), getHeight()); // fill rect
		getGraphics().setColor(Color.BLACK); // set color to black
		getGraphics().drawString(text, 1, 12); // draw text in rect
	}

	public String getText() { return text; }

}
