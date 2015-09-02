package core;

import java.util.Timer;
import java.util.TimerTask;
import java.util.LinkedList;
import java.util.HashMap;

import core.menu.Menu;
import core.menu.MenuList;
import misc.Account;
import misc.Debug;
import static misc.Serializer.*;
import network.NetworkDevice;

public class Main
{
	public static final int FRAME_INTERVAL = 40; // interval in which tick() and render() are called

	private static MenuList menuList;
	private static NetworkDevice networkDevice;
	private static Account account;

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

	public static void quit()
	{
		if (account != null)
		{
			Account.updateAccount(account);
		}
		Debug.quit("closed properly");
	}

	private void tick() // called by run()
	{
		menuList.tick(); // tick menuList
	}

	private void render() // called by run()
	{
		Screen.render(); // renders Screen
	}

	public static void setAccount(Account newAccount) { account = newAccount; }

	public static String getName() { return getAccount().getName(); }
	public static int getRank() { return getAccount().getRank(); }
	public static Account getAccount() { return account; }
	public static LinkedList<Menu> getMenues() { return getMenuList().getMenues(); } // returns menues, needed for MenuComponent
	public static MenuList getMenuList() { return menuList; } // needed in Screen.render()
	public static NetworkDevice getNetworkDevice() { return networkDevice; } // needed for the NetworkingMenues
}
