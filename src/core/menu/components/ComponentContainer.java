package core.menu.components;

import java.util.LinkedList;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;


public abstract class ComponentContainer extends MenuComponent
{
	private LinkedList<MenuComponent> components;

	public ComponentContainer(Menu menu, Rect rect)
	{
		super(menu, rect);
		components = new LinkedList<MenuComponent>();
	}

	@Override public void updateImage()
	{
		for (MenuComponent component : getComponents())
		{
			getGraphics().drawImage(component.getImage(), component.getX(), component.getY(), null);
		}
	}

	protected LinkedList<MenuComponent> getComponents() { return components; }
}
