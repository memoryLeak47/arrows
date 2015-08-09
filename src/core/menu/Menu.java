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
		// TODO: renders all needed menues
	}

	void onEvent(Event event)
	{
		// TODO: focusedComponent.on…
	}	

	public abstract boolean isFullscreen();
}
