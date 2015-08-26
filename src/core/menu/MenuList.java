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
	private LinkedList<Menu> menues;

	public MenuList()
	{
		menues = new LinkedList<Menu>();
		Screen.get().addMouseListener(this);
		Screen.get().addKeyListener(this);
		Screen.get().addMouseMotionListener(this);
		menues.add(new MainMenu());
	}

	public void tick()
	{
		getActiveMenu().tick();
	}

	public Menu getActiveMenu()
	{
		return menues.getLast();
	}

	private int getTopmostFullscreenMenuIndex()
	{
		for (int i = getMenues().size()-1; i >= 0; i--)
		{
			if (getMenues().get(i).isFullscreen())
			{
				return i;
			}
		}
		Debug.quit("MenuList.getTopmostFullscreenMenuIndex() return 0");
		return 0;
	}
	
	public void render()
	{
		for (int i = getTopmostFullscreenMenuIndex(); i < getMenues().size(); i++)
		{
			getMenues().get(i).render();
		}
	}

	void onEvent(EventPacket event)
	{
		menues.getLast().onEvent(event);
	}
	
	@Override public void mouseClicked(MouseEvent event) {}
	@Override public void mouseEntered(MouseEvent event) {}
	@Override public void mouseExited(MouseEvent event) {}
	@Override public void mouseDragged(MouseEvent event) {}

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
