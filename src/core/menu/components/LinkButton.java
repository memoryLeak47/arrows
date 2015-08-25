package core.menu.components;

import core.Main;
import core.menu.Menu;
import misc.math.Rect;

public class LinkButton extends Button
{
	private Menu target;

	public LinkButton(Menu menu, Rect rect, String caption, Menu target)
	{
		super(menu, rect, caption);
		this.target = target;
	}

	@Override public void onClick(int mouseButton)
	{
		Main.getMenues().add(target);
	}

}
