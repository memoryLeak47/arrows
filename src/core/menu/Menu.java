package core.menu;

import java.util.LinkedList;
import java.net.InetAddress;

import core.Main;
import core.Screen;
import core.menu.MenuComponent;
import core.menu.ComponentContainer;
import core.menu.menues.PopupMenu;
import network.Packet;
import network.game.packets.EventPacket;
import network.game.packets.events.*;
import misc.Debug;
import misc.math.Position;
import misc.math.Rect;

public abstract class Menu extends ComponentContainer
{
	private MenuComponent focusedComponent;

	public Menu(Rect rect)
	{
		super(null, rect);
	}

	public Menu()
	{
		super(null, new Rect(0,0,Screen.getScreenSize().getX(), Screen.getScreenSize().getY()));
		Debug.log("Menu.<init> -> Screen.getScreenSize(): " + Screen.getScreenSize());
	}

	public void tick() // ticks getComponents(), needed for <TODO>?
	{
		
		for (int i = 0; i < getComponents().size(); i++) // for all getComponents()
		{
			getComponents().get(i).tick(); // tick!
		}
		// Falls man nicht gehoverte MenuComponents ticken möchte
	}

	public void render() // renders getComponents()
	{
		for (int i = 0; i < getComponents().size(); i++) // for all getComponents()
		{
			getComponents().get(i).render(); // render image to Screen
		}
	}

	@Override protected MenuComponent getHoveredComponent() // calculates and sets the hoveredComponent
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

		return null; // returnt diese Komponente, falls in diesem ComponentContainer keine weiteren Components gehovert sind.
	}

	void onEvent(EventPacket event) // called by menu, handles events
	{
		if (event instanceof MouseMoveEventPacket) // if the mouse moved
		{
			if (getHoveredComponent() != null)
			{
				getHoveredComponent().onMouseMove(((MouseMoveEventPacket)event).getMousePosition());
			}
		}
		else if (event instanceof MouseButtonPressEventPacket) // if the mouse was pressed
		{
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

	protected final void popup(String text)
	{
		Main.getMenues().add(new PopupMenu(text));
	}

	// needed for checking what menues are to render
	public final boolean isFullscreen()
	{
		Debug.log("Menu.isFullscreen() -> getSize(): " + getSize() + " == Screen.getScreenSize(): " + Screen.getScreenSize());
		return (getSize().equals(Screen.getScreenSize()));
	}

	@Override public Position getOffset() { return new Position(getPosition()); }

	public final MenuComponent getFocusedComponent() { return focusedComponent; }
}
