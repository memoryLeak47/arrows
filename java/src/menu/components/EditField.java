package menu.components;

import java.awt.Color;

import core.Screen;
import menu.MenuComponent;
import menu.ComponentContainer;
import misc.math.pixel.PixelRect;

public class EditField extends MenuComponent
{
	private String text;

	public EditField(ComponentContainer parent, PixelRect rect, String text)
	{
		super(parent, rect);
		this.text = text; // set text
	}

	public EditField(ComponentContainer parent, PixelRect rect)
	{
		this(parent, rect, "");
	}

	@Override public void onKeyPress(char key)
	{	
		if (isEnabled())
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
	}

	@Override public void render()
	{
		if (isEnabled())
		{
			Screen.g().setColor(Color.BLUE);
		}
		else
		{
			Screen.g().setColor(Color.GRAY);
		}
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		Screen.g().setColor(Color.BLACK);
		Screen.g().drawString(text, getOffset().getX() + 1, getOffset().getY() + 12);
	}

	public String getText() { return text; }

}
