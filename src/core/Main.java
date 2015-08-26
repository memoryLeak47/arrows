package core;

import java.awt.Toolkit;
import java.util.Timer;
import java.util.TimerTask;
import java.util.LinkedList;

import core.menu.MenuList;
import network.NetworkDevice;
import core.menu.Menu;

public class Main
{
	public static final int FRAME_INTERVAL = 40;
	public static final int SCREEN_WIDTH = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth();
	public static final int SCREEN_HEIGHT = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight();

	private static MenuList menuList;
	private static NetworkDevice networkDevice;

	public static void main(String args[])
	{
		new Main().run();
	}

	private void run()
	{
		init();

		new Timer().scheduleAtFixedRate(new TimerTask()
		{
			@Override
			public void run()
			{
				tick();
				render();
			}
		}, FRAME_INTERVAL, FRAME_INTERVAL);
	}

	private void init()
	{
		Screen.init();
		menuList = new MenuList();
		networkDevice = new NetworkDevice();
	}

	private void tick()
	{
		menuList.tick();
		
	}

	private void render()
	{
		Screen.render();
	}

	public static Menu getActiveMenu() { return getMenuList().getActiveMenu(); }
	public static LinkedList<Menu> getMenues() { return getMenuList().getMenues(); }
	public static MenuList getMenuList() { return menuList; }
	public static NetworkDevice getNetworkDevice() { return networkDevice; }
}
