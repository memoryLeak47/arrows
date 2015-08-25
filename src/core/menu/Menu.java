package core.menu;

import java.util.LinkedList;

import core.menu.MenuComponent;
import network.packets.EventPacket;
import network.packets.events.*;
import core.Screen;

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

	private void calcHoveredComponent()
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

	void onEvent(EventPacket event)
	{
		if (event instanceof MouseMoveEventPacket)
		{
			calcHoveredComponent();
		}
		else if (event instanceof MouseButtonPressEventPacket)
		{
			calcHoveredComponent();
			if (getHoveredComponent() != null)
			{
				focusedComponent = getHoveredComponent();
			}
			else
			{
				focusedComponent = null;
			}
		}
		else if (event instanceof MouseButtonReleaseEventPacket)
		{
			if (getHoveredComponent() != null)
			{
				getHoveredComponent().onClick(((MouseButtonReleaseEventPacket) event).getMouseButton());
			}
		}
		else if (event instanceof KeyPressEventPacket)
		{
			if (getFocusedComponent() != null)
			{
				getFocusedComponent().onKeyPress(((KeyPressEventPacket) event).getKeyChar());
			}
		}
		else if (event instanceof KeyReleaseEventPacket)
		{
			if (getFocusedComponent() != null)
			{
				getFocusedComponent().onKeyRelease(((KeyReleaseEventPacket) event).getKeyChar());
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
