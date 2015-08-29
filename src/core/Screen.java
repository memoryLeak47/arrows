package core;

import javax.swing.JFrame;
import java.awt.Dimension;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.image.BufferStrategy;
import java.awt.Color;
import java.awt.Point;

import core.Main;
import misc.Debug;
import misc.JFrameListener;
import misc.math.Position;

public class Screen extends Canvas
{
	private static JFrame frame; // window
	private static Screen instance; // the Singleton instance, needed for doing stuff with a canvas like adding listeners
	private static Graphics g; // graphics for the BufferStrategy bs
	private static BufferStrategy bs;

	public static void init() // called by Main.init()
	{
		instance = new Screen("Arrows"); // creates the Singleton instance
	}

	private Screen(String caption)
	{
		// init stuff
		frame = new JFrame(caption); // creates window
		frame.add(this); // adds this Screen as Canvas to it
		frame.setSize(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT); // set Size of the window to Main.SCREEN_{WIDTH,HEIGHT}
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // window closes on pressing the x button
		frame.setVisible(true); // window is visible
		frame.setResizable(true); // to make it fullscreen
		frame.setFocusable(true); // listeners only work when frame is focused
		frame.addWindowListener(new JFrameListener());
		requestFocusInWindow();  // as above
	}

	public static void render() // called by Main.render() in a fixed rate
	{
		bs = get().getBufferStrategy(); // create bs to the Bufferstrategy of the singleton instance
		if (bs == null) // if it didn't work
		{
			get().createBufferStrategy(3); // create a BufferStrategy for the singleton instance
			return; // and return
		}
		g = bs.getDrawGraphics(); // if it worked, set g to the graphics of the bs
		g.setColor(Color.BLACK); // clear Screen
		g.fillRect(0, 0, Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT); // as above
		Main.getMenuList().render(); // render the menuList
		g.dispose(); // dispose the graphics
		bs.show(); // flip the buffer(strategy)
	}

	public static Position getCursorPosition() // returns cursor position or null when Mouse is out of Screen
	{
		Point position = get().getMousePosition();
		if (position == null) // if mouse is out of screen
		{
			return null; // return null
		}
		return new Position(position.x, position.y); // return mousePosition as Position
	}

	public static Graphics g() { return g; } // returns graphics or bs, needed for rendering
	public static Screen get() { return instance; } // returns singleton instance
}
