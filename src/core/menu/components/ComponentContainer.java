package core.menu.components;

import java.util.LinkedList;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;
import misc.math.Position;

public abstract class ComponentContainer extends MenuComponent // abstract for not instanciating
{
	private LinkedList<MenuComponent> components; // list of components
	private MenuComponent hoveredComponent;
	private Position cursorPosition;

	public ComponentContainer(Menu menu, Rect rect)
	{
		super(menu, rect);
		components = new LinkedList<MenuComponent>(); // create components
		cursorPosition = new Position(0,0);
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

	@Override public void onMouseMove(Position mousePos)
	{
		calcCursorPosition(mousePos);

		// bestimmen von hoveredComponent
		for (MenuComponent component : getComponents())
		{
			if (this.getCursorPosition().inRect(component))
			{
				hoveredComponent = component;
				break;
			}
		}

	}

	public void calcCursorPosition(Position mousePos)
	{
		cursorPosition.setX(mousePos.getX() - this.getX());
		cursorPosition.setY(mousePos.getY() - this.getY());
	}

	protected LinkedList<MenuComponent> getComponents() { return components; } // needed for the subclasses
	public Position getCursorPosition() { return cursorPosition; }
	public MenuComponent getHoveredComponent() { return hoveredComponent; }
}
