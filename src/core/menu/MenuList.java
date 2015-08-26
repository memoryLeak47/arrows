package core.menu;

import java.util.LinkedList;
import java.awt.event.MouseListener;
import java.awt.event.KeyListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.event.KeyEvent;

import core.menu.Menu;
import core.menu.menues.MainMenu;
import network.game.packets.EventPacket;
import network.game.packets.events.*;
import core.Screen;
import misc.Debug;

public class MenuList implements MouseMotionListener, MouseListener, KeyListener
{
	private LinkedList<Menu> menues; // all menues

	public MenuList()
	{
		menues = new LinkedList<Menu>(); // creates menues
		menues.add(new MainMenu()); // adds MainMenu

		// adds 'this'-listener to the Screen
		Screen.get().addMouseListener(this);
		Screen.get().addKeyListener(this);
		Screen.get().addMouseMotionListener(this);
	}

	public void tick() // ticks topmost menu
	{
		getTopmostMenu().tick();
	}

	public Menu getTopmostMenu()
	{
		return menues.getLast();
	}

	private int getTopmostFullscreenMenuIndex() // needed for knowing what menu is to render, see 'Menu.isFullscreen()'
	{
		for (int i = getMenues().size()-1; i >= 0; i--) // for all menues (count from back to front)
		{
			if (getMenues().get(i).isFullscreen()) // if you are fullscreen
			{
				return i; // return your index
			}
		}
		Debug.quit("MenuList.getTopmostFullscreenMenuIndex() no fullscreen menu!"); // if none is fullscreen, error and quit
		return 0;
	}
	
	public void render()
	{
		for (int i = getTopmostFullscreenMenuIndex(); i < getMenues().size(); i++)
		// for all menues on top of the topmost fullscreen menu (including it)
		{
			getMenues().get(i).render(); // render
		}
	}

	void onEvent(EventPacket event) // give event to topmost menu
	{
		getTopmostMenu().onEvent(event);
	}
	
	// not needed listener functions
	@Override public void mouseClicked(MouseEvent event) {}
	@Override public void mouseEntered(MouseEvent event) {}
	@Override public void mouseExited(MouseEvent event) {}
	@Override public void mouseDragged(MouseEvent event) {}

	// needed listener functions, give event to this.onEvent(...)
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

	@Override public void keyTyped(KeyEvent event) {}

	public LinkedList<Menu> getMenues() { return menues; }
}
