package core.menu;

import java.util.LinkedList;
import java.net.InetAddress;

import core.menu.MenuComponent;
import core.Screen;
import network.Packet;
import network.game.packets.EventPacket;
import network.game.packets.events.*;
import misc.Debug;
import misc.math.Position;

public abstract class Menu
{
	private LinkedList<MenuComponent> menuComponents; // the menuComponents
	private MenuComponent focusedComponent, hoveredComponent;

	public Menu() // constructor
	{
		menuComponents = new LinkedList<MenuComponent>(); // creates the list menuComponents
	}

	public void tick() // ticks menuComponents, needed for <TODO>?
	{
		
		for (int i = 0; i < menuComponents.size(); i++) // for all menuComponents
		{
			menuComponents.get(i).tick(); // tick!
		}
		// Falls man nicht gehoverte MenuComponents ticken möchte
	}

	public void render() // renders menuComponents
	{
		for (int i = 0; i < menuComponents.size(); i++) // for all menuComponents
		{
			menuComponents.get(i).render(); // render image to Screen
		}
	}

	private void calcHoveredComponent() // calculates and sets the hoveredComponent
	{
		Position cursor = Screen.getCursorPosition();
		if (cursor != null) // if the cursor is in Screen
		{
			for (int i = menuComponents.size()-1; i >= 0; i--) // for all components (counting from back to front, because last component is rendered ontop)
			{
				if (cursor.inRect(menuComponents.get(i))) // if the mouse points at you
				{
					hoveredComponent = menuComponents.get(i); // be hovered
					return; // done
				}
			} // if none is hovered
		} // or if mouse is out of screen
		hoveredComponent = null; // set hoveredComponent to null
	}

	void onEvent(EventPacket event) // called by menu, handles events
	{
		if (event instanceof MouseMoveEventPacket) // if the mouse moved
		{
			calcHoveredComponent(); // check if the hoveredComponent has changed
		}
		else if (event instanceof MouseButtonPressEventPacket) // if the mouse was pressed
		{
			calcHoveredComponent(); // check if the hoveredComponent has changed (like when pressing a button which links to another menu)
			if (getHoveredComponent() != null) // if there is a hoveredComponent
			{
				focusedComponent = getHoveredComponent(); // let it be the focusedComponent
			}
			else // else
			{
				focusedComponent = null; // there is no focusedComponent
			}
		}
		else if (event instanceof MouseButtonReleaseEventPacket) // if the mouse was released
		{
			if (getHoveredComponent() != null) // and there is a hoveredComponent
			{
				getHoveredComponent().onClick(((MouseButtonReleaseEventPacket) event).getMouseButton()); // call onClick to it
			}
		}
		else if (event instanceof KeyPressEventPacket) // if a keyboard-key was pressed
		{
			if (getFocusedComponent() != null) // and there is a focused component
			{
				getFocusedComponent().onKeyPress(((KeyPressEventPacket) event).getKeyChar()); // call onKeyPress to it
			}
		}
		else if (event instanceof KeyReleaseEventPacket) // if a key was released
		{
			if (getFocusedComponent() != null) // and there is a focused component
			{
				getFocusedComponent().onKeyRelease(((KeyReleaseEventPacket) event).getKeyChar()); // call onKeyRelease to it
			}
		}
		else // if the event is none of these
		{
			Debug.quit("bad Event-subclass"); // print error and quit
		}
	}

	public final MenuComponent getFocusedComponent() { return focusedComponent; }
	public final MenuComponent getHoveredComponent() { return hoveredComponent; }
	protected final LinkedList<MenuComponent> getComponents() { return menuComponents; }

	public abstract boolean isFullscreen(); // needed for checking what menues are to render
	// because you can't see menues which are under a fullscreen-menu
}
