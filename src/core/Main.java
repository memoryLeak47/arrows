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
	public static final int FRAME_INTERVAL = 40; // interval in which tick() and render() are called
	public static final int SCREEN_WIDTH = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth(); // max width of your screen
	public static final int SCREEN_HEIGHT = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight(); // max height of your screen

	private static MenuList menuList;
	private static NetworkDevice networkDevice;

	public static void main(String args[])
	{
		new Main().run(); // create new Main instance and run it
	}

	private void run() // called by main(...)
	{
		init(); // init then

		new Timer().scheduleAtFixedRate(new TimerTask() // repeat @ fixed rate <FRAME_INTERVAL>
		{
			@Override
			public void run()
			{
				tick(); // tick
				render(); // render
			}
		}, FRAME_INTERVAL, FRAME_INTERVAL);

		while (true) // repeat forever
		{
			networkDevice.receive(); // receive packets in networkDevice
		}
	}

	private void init() // called by run()
	{
		Screen.init(); // init Screen
		menuList = new MenuList(); // create menuList
		networkDevice = new NetworkDevice(); // create networkDevice
	}

	private void tick() // called by run()
	{
		menuList.tick(); // tick menuList
	}

	private void render() // called by run()
	{
		Screen.render(); // renders Screen
	}

	public static LinkedList<Menu> getMenues() { return getMenuList().getMenues(); } // returns menues, needed for MenuComponent
	public static MenuList getMenuList() { return menuList; } // needed in Screen.render()
	public static NetworkDevice getNetworkDevice() { return networkDevice; } // needed for the NetworkingMenues
}
