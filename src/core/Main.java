package core;

import java.util.Timer;
import java.util.TimerTask;
import java.awt.Toolkit;

import core.menu.MenuList;
import network.NetworkDevice;

public class Main
{
	public static final int FRAME_INTERVAL = 40;
	public static final int SCREEN_WIDTH = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth();
	public static final int SCREEN_HEIGHT = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight();

	private static MenuList menuList;
	private NetworkDevice networkDevice;

	public static void main(String args[])
	{
		new Main().run();
	}

	private void run()
	{
		init();

		Timer timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask()
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
	}

	private void tick()
	{
		if (networkDevice != null)
		{
			networkDevice.tick();
		}
		
	}

	private void render()
	{
		menuList.render();
		Screen.update();
	}
}
