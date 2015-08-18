package core.menu.components;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class EditField extends MenuComponent
{
	String text;

	public EditField(Menu menu, Rect rect, String text)
	{
		super(menu, rect);
		this.text = text;
	}

	@Override
	public void onKeyPress(char key)
	{	
		if (((int) key) == 8)
			text = text.substring(0,text.length()-1);

		if (!misc.KeyChecker.isSign(key))
			return;

		else
			text += key;
	}

	@Override
	public void render()
	{
		core.Screen.g().setColor(java.awt.Color.BLUE);
		core.Screen.g().fillRect(getPosition().getX(), getPosition().getY(), getSize().getX(), getSize().getY());
		core.Screen.g().setColor(java.awt.Color.BLACK);
		core.Screen.g().drawString(text, getPosition().getX() + 1, getPosition().getY() + 12);
	}

}
