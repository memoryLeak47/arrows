package core.menu.menues;

import core.menu.Menu;
import core.menu.components.*;
import misc.math.*;

public class PopupMenu extends Menu
{
	private String text;

	public PopupMenu(String text)
	{
		super(new Rect(30, 30, 400, 300));
		this.text = text;
		getComponents().add(new Panel(this, new Rect(new Position(0, 0), getSize())));
		getComponents().add(new Label(this, new Rect(getSize().getX()/2-60, 20, 120, 20), text));
		getComponents().add(new BackButton(this, new Rect(getSize().getX()/2 - 30, 50, 60, 20)));
	}
}
