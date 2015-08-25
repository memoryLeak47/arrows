package core.menu;

import java.util.LinkedList;

import core.menu.MenuComponent;
import network.sendable.Event;
import core.Screen;
import network.sendable.events.*;

public abstract class Menu
{
	private LinkedList<MenuComponent> menuComponents;
	private MenuComponent focusedComponent, hoveredComponent;

	public Menu()
	{
		menuComponents = new LinkedList<MenuComponent>();
	}

	public void tick()
	{
		for (int i = 0; i < menuComponents.size(); i++)
		{
			menuComponents.get(i).tick();
		}
	}

	public void render()
	{
		for (int i = 0; i < menuComponents.size(); i++)
		{
			menuComponents.get(i).render();
		}
	}

	void onEvent(Event event)
	{
		if (event instanceof MouseMove)
		{
			for (int i = menuComponents.size()-1; i >= 0; i--)
			{
				if (Screen.getCursorPosition().inRect(menuComponents.get(i)))
				{
					hoveredComponent = menuComponents.get(i);
					return;
				}
			}
			hoveredComponent = null;
		}
		else if (event instanceof MouseButtonPress)
		{
			if (getHoveredComponent() != null)
			{
				focusedComponent = getHoveredComponent();
			}
			else
			{
				focusedComponent = null;
			}
		}
		else if (event instanceof MouseButtonRelease)
		{
			if (getHoveredComponent() != null)
			{
				getHoveredComponent().onClick(((MouseButtonRelease) event).getMouseButton());
			}
		}
		else if (event instanceof KeyPress)
		{
			if (getFocusedComponent() != null)
			{
				getFocusedComponent().onKeyPress(((KeyPress) event).getKeyChar());
			}
		}
		else if (event instanceof KeyRelease)
		{
			if (getFocusedComponent() != null)
			{
				getFocusedComponent().onKeyRelease(((KeyRelease) event).getKeyChar());
			}
		}
		else
		{
			System.out.println("bad Event-subclass");
		}
	}

	protected final void add(MenuComponent menuComponent)
	{
		menuComponents.add(menuComponent);
	}

	public final MenuComponent getFocusedComponent() { return focusedComponent; }
	public final MenuComponent getHoveredComponent() { return hoveredComponent; }

	public abstract boolean isFullscreen();
}
