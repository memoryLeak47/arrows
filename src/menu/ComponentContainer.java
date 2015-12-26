package menu;

import java.util.LinkedList;

import core.Screen;
import menu.MenuComponent;
import menu.Menu;
import misc.Debug;
import misc.math.menu.MenuRect;
import misc.math.menu.MenuPosition;

public abstract class ComponentContainer extends MenuComponent // abstract for not instanciating
{
	private LinkedList<MenuComponent> components; // list of components

	public ComponentContainer(ComponentContainer parent, MenuRect rect)
	{
		super(parent, rect);
		components = new LinkedList<MenuComponent>(); // create components
	}

	@Override public void render() // sets image to the addition of all other images
	{
		for (MenuComponent component : getComponents()) // for all components
		{
			component.render();
		}
	}

	// returnt cursor position relativ zu sich
	public MenuPosition getCursorMenuPosition() 
	{ 
		MenuPosition pos = Screen.getCursorPosition();
		if (pos == null)
		{
			return null;
		}
		return pos.minus(getOffset());
	}

	// kalkuliert und setzt hoveredComponent
	protected final MenuComponent getHoveredComponent()
	{
		MenuPosition cursor = Screen.getCursorPosition();
		if (cursor != null) // wenn der cursor im fenster ist
		{
			for (int i = getComponents().size()-1; i >= 0; i--) // für alle Components (als letzes gerendert liegt ganz oben -> von hinten nach vorne)
			{
				if (cursor.inMenuRect(getComponents().get(i))) // wenn die maus auf die Component zeigt
				{
					// und diese Component ein ComponentContainer ist der selbst eine gehoverte Component hat
					if (getComponents().get(i) instanceof ComponentContainer && ((ComponentContainer) getComponents().get(i)).getHoveredComponent() != null) // and you are a ComponentContainer
					{
						return ((ComponentContainer) getComponents().get(i)).getHoveredComponent(); // returne seine gehoverte Component
					} // falls nicht
					return getComponents().get(i); // returne ihn selbst
				}
			} // wenn keine Component gefunden wurde
		} // oder die maus außerhalb des fensters ist

		return null; // returne null
	}

	protected LinkedList<MenuComponent> getComponents() { return components; } // die unterklassen brauchen dies
	public MenuComponent getFocusedComponent() { return getParentMenu().getFocusedComponent(); } // Nur die Menu Klasse speichert die Focused Component
}
