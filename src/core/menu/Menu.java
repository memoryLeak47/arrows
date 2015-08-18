package core.menu;

import java.util.LinkedList;

import core.menu.MenuComponent;
import network.sendable.Event;

public abstract class Menu
{
	LinkedList<MenuComponent> menuComponents;
	MenuComponent focusedComponent;

	public Menu() // ?
	{
		menuComponents = new LinkedList<MenuComponent>();
		// TODO
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
		// TODO: renders all needed menuComponents
		for (int i = 0; i < menuComponents.size(); i++)
		{
			menuComponents.get(i).render();
		}
	}

	void onEvent(Event event)
	{
		// TODO: focusedComponent.on…
	}

	protected final void add(MenuComponent menuComponent)
	{
		menuComponents.add(menuComponent);
	}

	public final MenuComponent getFocusedComponent()
	{
		return focusedComponent;
	}

	public abstract boolean isFullscreen();
}
