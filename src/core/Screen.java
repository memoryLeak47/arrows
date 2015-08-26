package core;

import javax.swing.JFrame;
import java.awt.Dimension;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.image.BufferStrategy;
import java.awt.Color;

import misc.math.Position;
import misc.Debug;

public class Screen extends Canvas
{
	public static final int SCREEN_WIDTH = 1200, SCREEN_HEIGHT = 1000;
	private static JFrame frame;
	private static Screen instance;
	private static Graphics g;
	private static BufferStrategy bs;

	public static void init()
	{
		instance = new Screen("GameNetworking - CatchGame");
	}

	private Screen(String caption)
	{
		// init stuff
		frame = new JFrame(caption);
		frame.add(this);
		frame.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
		frame.setFocusable(true);
		setFocusable(true);
		requestFocusInWindow();
	}

	public static void render()
	{
		bs = get().getBufferStrategy();
		if (bs == null)
		{
			get().createBufferStrategy(3);
			return;
		}
		g = bs.getDrawGraphics();
		g.setColor(Color.GREEN); // clears ...
		g.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // ... screen
		// RENDER
		Main.getMenuList().render();
		// }
		g.dispose();
		bs.show();
	}

	public static Position getCursorPosition()
	{
		if (get().getMousePosition() == null)
		{
			return new Position(-1,-1);
		}
		return new Position(get().getMousePosition().x, get().getMousePosition().y);
	}

	public static Graphics g() { return g; }
	public static Screen get() { return instance; }
}
