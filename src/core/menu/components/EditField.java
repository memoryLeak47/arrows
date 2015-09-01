package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.ComponentContainer;
import misc.math.Rect;

public class EditField extends MenuComponent
{
	private String text;

	public EditField(ComponentContainer parent, Rect rect, String text)
	{
		super(parent, rect);
		this.text = text; // set text
	}

	public EditField(ComponentContainer parent, Rect rect)
	{
		this(parent, rect, "");
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
		}

		if (!misc.KeyChecker.isSign(key)) // if the key is not a valid sign
		{
			return; // return 
		}
		else // else
		{
			text += key; // add it to text
		}
	}

	@Override public void render() // TODO make prettier
	{
		Screen.g().setColor(Color.BLUE); // set color to blue
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // fill rect
		Screen.g().setColor(Color.BLACK); // set color to black
		Screen.g().drawString(text, getOffset().getX() + 1, getOffset().getY() + 12); // draw text in rect
	}

	public String getText() { return text; }

}
