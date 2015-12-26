package menu;

import java.util.LinkedList;
import java.net.InetAddress;
import java.awt.Color;

import core.Main;
import core.Screen;
import menu.MenuComponent;
import menu.ComponentContainer;
import menu.menues.PopupMenu;
import network.Packet;
import network.game.packets.EventPacket;
import network.game.packets.events.*;
import misc.Debug;
import misc.math.menu.MenuPosition;
import misc.math.menu.MenuRect;

public abstract class Menu extends ComponentContainer
{
	private MenuComponent focusedComponent; // die fokusierte component

	// erstellung eines menues mit angegebenem rect (position und größe)
	public Menu(MenuRect rect)
	{
		super(null, rect);
	}

	// erstellung eines fullscreen-menues
	public Menu()
	{
		super(null, new MenuRect(0,0,Screen.getScreenSize().getX(), Screen.getScreenSize().getY()));
	}

	// tickt alle components
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
		// Übermalen mit schwarz
		Screen.g().setColor(Color.BLACK);
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		// Komponenten zeichnen
		super.render();
	}

	// bearbeitet die events vom menu
	protected void onEvent(EventPacket event)
	{
		if (event instanceof MouseMoveEventPacket) // wenn sich die maus bewegt hat
		{
			MenuComponent hovered = getHoveredComponent(); // Verhinderung einer null-pointer-exception
			if (hovered != null) // und es eine gehoverte MenuComponent gibt
			{
				hovered.onMouseMove(((MouseMoveEventPacket)event).getMouseMenuPosition()); // gebe das event an getHoveredComponent() weiter
			}
		}
		else if (event instanceof MouseButtonPressEventPacket) // wenn die maus gedrückt wurde
		{
			focusedComponent = getHoveredComponent(); // lasse die fokusierte MenuComponent die gehoverte sein
		}
		else if (event instanceof MouseButtonReleaseEventPacket) // wenn die maus losgelassen wurde
		{
			MenuComponent hovered = getHoveredComponent();
			if (hovered != null) // und es eine gehoverte MenuComponent gibt
			{
				hovered.onClick(((MouseButtonReleaseEventPacket) event).getMouseButton()); // gebe das event an getHoveredComponent() weiter
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
			Debug.error("bad Event-subclass"); // printe nen error und beende das programm
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

	// MenuPosition relativ zum Screen (bei Menu: Offset == MenuPosition)
	@Override public MenuPosition getOffset() { return new MenuPosition(getPosition()); }

	// wird von ComponentContainer.getFocusedComponent() genutzt
	@Override public final MenuComponent getFocusedComponent() { return focusedComponent; }
}
