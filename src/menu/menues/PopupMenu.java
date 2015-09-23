package menu.menues;

import core.Screen;
import menu.Menu;
import menu.components.*;
import misc.math.*;

public class PopupMenu extends Menu
{
	private String text;

	public PopupMenu(String text)
	{
		super(new Rect(Screen.getScreenSize().getX()/2-200, Screen.getScreenSize().getY()/2-150, 400, 300));
		this.text = text;
		getComponents().add(new Panel(this, new Rect(new Position(0, 0), getSize())));
		getComponents().add(new Label(this, new Rect(200-150, 20, 300, 20), text));
		getComponents().add(new BackButton(this, new Rect(200-30, 50, 60, 20)));
	}
}
