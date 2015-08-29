package core.menu.menues;

import core.menu.Menu;
import core.menu.components.*;
import misc.math.*;

public class PopupMenu extends Menu
{
	private String text;

	public PopupMenu(String text)
	{
		this.text = text;
		getComponents().add(new Label(this, new Rect(400-text.length()*6, 20, text.length()*12, 20), text));
		getComponents().add(new BackButton(this, new Rect(370, 50, 60, 20)));
	}

	@Override public boolean isFullscreen() { return true; }
}
