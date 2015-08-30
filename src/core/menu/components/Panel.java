package core.menu.components;

import java.awt.Color;

import core.menu.components.ComponentContainer;
import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;
import misc.math.Size;

public class Panel extends ComponentContainer
{
	private static final Size padding = new Size(20, 20); // über "padding" wird der Abstand innerhalb des KomponentenContainers zu den Komponenten gespeichert. Wird in calcSize() benötigt

	public Panel(Menu menu, Rect rect)
	{
		super(menu, rect);
		updateImage();
	}

	@Override public void updateImage()
	{
		super.updateImage(); // draw content of all components
		getGraphics().setColor(Color.BLUE); // set color to blue
		getGraphics().drawRect(0, 0, getWidth()-1, getHeight()-1); // draw border
	}

	// ändert die Size des Panels so, dass zwischen der Komponente links unten noch padding Platz ist
	public void calcSize()
	{
		int right = 0;
		int bot = 0;

		// sucht die width/height indem alle Komponenten durchlaufen werden und die am weitesten rechts und unten gespeichert werden
		for (MenuComponent component : getComponents())
		{
			right = Math.max(right, component.getRight() + padding.getX());
			bot = Math.max(bot, component.getBot() + padding.getY());
		}

		if (right != this.getWidth())
		{
			this.setWidth(right);
		}

		if (bot != this.getHeight())
		{
			this.setHeight(bot);
		}
	}
}
