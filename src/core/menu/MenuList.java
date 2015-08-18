package core.menu;

import java.util.LinkedList;

import core.menu.Menu;
import core.menu.menues.MainMenu;
import network.sendable.Event;

public class MenuList // TODO: implements Listener
{
	private LinkedList<Menu> menues;

	public MenuList()
	{
		menues = new LinkedList<Menu>();
		menues.add(new MainMenu());
		// TODO: Screen.get().addListeners…(this);
	}

	public void tick()
	{
		getActiveMenu().tick();
	}

	public Menu getActiveMenu()
	{
		return menues.getLast();
	}
	
	public void render()
	{
		// TODO
		menues.getLast().render();
	}

	void onEvent(Event event)
	{
		menues.getLast().onEvent(event);
	}
}
