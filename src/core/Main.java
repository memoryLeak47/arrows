package core;

import java.util.Timer;
import java.util.TimerTask;

import core.menu.MenuList;

public class Main
{
	public static final int FRAME_INTERVAL = 40;

	private static MenuList menuList;
	// private NetworkDevice networkDevice;

	public static void main(String args[])
	{
		new Main().run();
	}

	public void run()
	{
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

	public void tick()
	{
		
	}

	public void render()
	{
		menuList.render();
		Screen.update();
	}
}
