package menu;

import java.util.LinkedList;
import java.awt.event.MouseListener;
import java.awt.event.KeyListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.event.KeyEvent;

import menu.Menu;
import menu.menues.LoginMenu;
import network.game.packets.EventPacket;
import network.game.packets.events.*;
import core.Screen;
import misc.Debug;

public class MenuList implements MouseMotionListener, MouseListener, KeyListener
{
	private LinkedList<Menu> menues; // alle menues

	// wenn eine MenuList erstellt wird (nur einmal am anfang des programms)
	public MenuList()
	{
		menues = new LinkedList<Menu>(); // erstelle die menu-liste
		menues.add(new LoginMenu()); // füge das login-menu hinzu

		// füge die eigenen listener zum Screen hinzu
		Screen.get().addMouseListener(this);
		Screen.get().addKeyListener(this);
		Screen.get().addMouseMotionListener(this);
	}

	// tickt das oberste menu
	public void tick()
	{
		getTopmostMenu().tick();
	}

	// returne das oberste menu
	public Menu getTopmostMenu()
	{
		return menues.getLast();
	}

	// returne den index des obersten menues
	private int getTopmostFullscreenMenuIndex()
	{
		for (int i = getMenues().size()-1; i >= 0; i--) // für alle menues (von hinten nach vorne)
		{
			if (getMenues().get(i).isFullscreen()) // wenn du fullscreen bist
			{
				return i; // returne deinen index
			}
		} // wenn keins fullscreen ist
		Debug.error("MenuList.getTopmostFullscreenMenuIndex() no fullscreen menu!"); // beende das programm und schmeiß nen error
		return 0;
	}

	// zeiche alle sichtbaren menues
	public void render()
	{
		for (int i = getTopmostFullscreenMenuIndex(); i < getMenues().size(); i++)
		// für alle menues die auf dem obersten fullscreen menu liegen (und dem obersten fullscreen-menu)
		{
			getMenues().get(i).render(); // render
		}
	}

	// gebe das event an das oberste menu weiter
	void onEvent(EventPacket event)
	{
		getTopmostMenu().onEvent(event);
	}
	
	// nutzlose event-funktionen der listener
	@Override public void mouseClicked(MouseEvent event) {}
	@Override public void mouseEntered(MouseEvent event) {}
	@Override public void mouseExited(MouseEvent event) {}
	@Override public void mouseDragged(MouseEvent event) {}
	@Override public void keyTyped(KeyEvent event) {}

	// gebrauchte event-funktionen der listener -> gebe event weiter an onEvent(Event)
	@Override public void mousePressed(MouseEvent event)
	{
		onEvent(new MouseButtonPressEventPacket(event));
	}

	@Override public void mouseReleased(MouseEvent event)
	{
		onEvent(new MouseButtonReleaseEventPacket(event));
	}

	@Override public void mouseMoved(MouseEvent event)
	{
		onEvent(new MouseMoveEventPacket(event));
	}

	@Override public void keyPressed(KeyEvent event)
	{
		onEvent(new KeyPressEventPacket(event));
	}

	@Override public void keyReleased(KeyEvent event)
	{
		onEvent(new KeyReleaseEventPacket(event));
	}

	// returnt alle menues
	public LinkedList<Menu> getMenues() { return menues; }
}
