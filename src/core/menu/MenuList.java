package core.menu;

import java.util.LinkedList;

import core.menu.Menu;

public class MenuList
{
	private LinkedList<Menu> menuList;

	public void tick()
	{
		getTopMenu().tick();
	}

	public Menu getTopMenu()
	{
		return menuList.getLast();
	}
	
	public void render()
	{
		
	}
}
