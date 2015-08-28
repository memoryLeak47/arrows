package core.menu.components;

import java.awt.image.BufferedImage;

import core.menu.Menu;
import core.menu.MenuComponent;
import core.menu.components.Panel;
import misc.math.Rect;

public class ScrollPanel extends Panel
{
	public ScrollPanel(Menu menu, Rect rect)
	{
		super(menu, rect);
	}

	@Override public void addComponent(MenuComponent component)
	{
		super.addComponent(component);

	}

	@Override public void updateImage()
	{
		resizeImage();
		if (getImage().getWidth() > this.getWidth())
		{
			// TODO: waagerechten Scrollbalken rendern
		}

		if (getImage().getHeight() > this.getHeight())
		{
			// TODO: senkrechten Scrollbalken rendern
		}
		
	}

	private final void resizeImage()
	{
		int right = 0;
		int bot = 0;
		for (MenuComponent component : getComponents())
		{
			if (component.getBot() > bot)
			{
				bot = component.getBot();
			}

			if (component.getRight() > right) // wenn hinzugefügte Component weiter unten ist als das jBild groß ist, dann
			{
				right = component.getRight();
				
				// image.height vergrößern
			}
		}

		if (right != getImage().getWidth() || bot != getImage().getHeight())
		{
			setImage(new BufferedImage(right, bot, BufferedImage.TYPE_INT_ARGB));
		}
	}
}
