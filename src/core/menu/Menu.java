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
	private MenuComponent focusedComponent; // die fokusierte component

	// erstellung eines menues mit angegebenem rect (position und größe)
	public Menu(Rect rect)
	{
		super(null, rect);
	}

	// erstellung eines fullscreen-menues
	public Menu()
	{
		super(null, new Rect(0,0,Screen.getScreenSize().getX(), Screen.getScreenSize().getY()));
	}

	// tickt alle components, needed for <TODO>
	public void tick()
	{
		for (int i = 0; i < getComponents().size(); i++) // für alle components
		{
			getComponents().get(i).tick(); // tick
		}
	}

	// rendert alle components
	public void render()
	{
		for (int i = 0; i < getComponents().size(); i++) // für alle components
		{
			getComponents().get(i).render(); // render to Screen
		}
	}

	// bearbeitet die events vom menu
	void onEvent(EventPacket event)
	{
		if (event instanceof MouseMoveEventPacket) // wenn sich die maus bewegt hat
		{
			if (getHoveredComponent() != null) // und es eine gehoverte MenuComponent gibt
			{
				getHoveredComponent().onMouseMove(((MouseMoveEventPacket)event).getMousePosition()); // gebe das event an getHoveredComponent() weiter
			}
		}
		else if (event instanceof MouseButtonPressEventPacket) // wenn die maus gedrückt wurde
		{
			focusedComponent = getHoveredComponent(); // lasse die fokusierte MenuComponent die gehoverte sein
		}
		else if (event instanceof MouseButtonReleaseEventPacket) // wenn die maus losgelassen wurde
		{
			if (getHoveredComponent() != null) // und es eine gehoverte MenuComponent gibt
			{
				getHoveredComponent().onClick(((MouseButtonReleaseEventPacket) event).getMouseButton()); // gebe das event an getHoveredComponent() weiter
			}
		}
		else if (event instanceof KeyPressEventPacket) // wenn die tastatur gedrückt wurde
		{
			if (getFocusedComponent() != null) // und es eine fokusierte MenuComponent gibt 
			{
				getFocusedComponent().onKeyPress(((KeyPressEventPacket) event).getKeyChar()); // gebe das event an getFocusedComponent() weiter
			}
		}
		else if (event instanceof KeyReleaseEventPacket) // wenn die tastatur losgelassen wurde
		{
			if (getFocusedComponent() != null) // und es eine fokusierte MenuCompoent gibt
			{
				getFocusedComponent().onKeyRelease(((KeyReleaseEventPacket) event).getKeyChar()); // gebe das event an getFocusedComponent() weiter
			}
		}
		else // falls das event ein anderes ist
		{
			Debug.quit("bad Event-subclass"); // printe nen error und beende das programm
		}
	}

	// öffnet ein popup menu mit text als information
	protected static final void popup(String text)
	{
		Main.getMenues().add(new PopupMenu(text));
	}

	// gebraucht um zu wissen welches menu welches verdeckt (rendern)
	public final boolean isFullscreen()
	{
		return (getSize().equals(Screen.getScreenSize()));
	}

	// <TODO>
	@Override public Position getOffset() { return new Position(getPosition()); }

	public final MenuComponent getFocusedComponent() { return focusedComponent; }
}
