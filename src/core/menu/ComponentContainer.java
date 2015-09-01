package core.menu;

import java.util.LinkedList;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;
import misc.math.Position;

public abstract class ComponentContainer extends MenuComponent // abstract for not instanciating
{
	private LinkedList<MenuComponent> components; // list of components

	public ComponentContainer(ComponentContainer parent, Rect rect)
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

	public Position getCursorPosition() 
	{ 
		Position cursorPos = new Position(Screen.getCursorPosition());
		cursorPos.subtract(getOffset());
		return cursorPos;
	}
	
	protected MenuComponent getHoveredComponent() // calculates and sets the hoveredComponent
	{
		Position cursor = Screen.getCursorPosition();
		if (cursor != null) // if the cursor is in Screen
		{
			for (int i = getComponents().size()-1; i >= 0; i--) // for all components (counting from back to front, because last component is rendered ontop)
			{
				if (cursor.inRect(getComponents().get(i))) // if the mouse points at you
				{
					if (getComponents().get(i) instanceof ComponentContainer)
					{
						return ((ComponentContainer) getComponents().get(i)).getHoveredComponent(); // be hovered
					}
					return getComponents().get(i); // be hovered
				}
			}
		} // or if mouse is out of screen

		return this; // returnt diese Komponente, falls in diesem ComponentContainer keine weiteren Components gehovert sind.
	}

	protected LinkedList<MenuComponent> getComponents() { return components; } // needed for the subclasses
	public MenuComponent getFocusedComponent() { return getParent().getFocusedComponent(); } // Nur die Menu Klasse speichert die Focused Component
}
