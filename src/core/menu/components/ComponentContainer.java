package core.menu.components;

import java.util.LinkedList;

import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;

public abstract class ComponentContainer extends MenuComponent // abstract for not instanciating
{
	private LinkedList<MenuComponent> components; // list of components

	public ComponentContainer(Menu menu, Rect rect)
	{
		super(menu, rect);
		components = new LinkedList<MenuComponent>(); // create components
	}

	@Override public void updateImage() // sets image to the addition of all other images
	{
		for (MenuComponent component : getComponents()) // for all components
		{
			getGraphics().drawImage(component.getImage(), component.getX(), component.getY(), null); // draw their picture on this.getGraphics() relative to the position of the ComponentContainer
		}
	}

	public void addComponent(MenuComponent component)
	{
		components.add(component);
		updateImage();
	}
	
	protected LinkedList<MenuComponent> getComponents() { return components; } // needed for the subclasses
}
