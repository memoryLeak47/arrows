package core.menu.components;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public class Label extends MenuComponent
{
	private String caption;

	public Label(Menu menu, Rect rect, String caption)
	{
		super(menu, rect);
		this.caption = caption;
		updateImage();
	}

	@Override public void updateImage()
	{
		getGraphics().setColor(java.awt.Color.GREEN);
		getGraphics().fillRect(0, 0, getSize().getX(), getSize().getY());
		getGraphics().setColor(java.awt.Color.BLACK);
		getGraphics().drawString(caption, 1, 12);
	}

}
