package core;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.Color;

import core.Main;

public class Screen extends JPanel
{
	public static final int CAM_OFFSET = 16;
	public static int camXOffset = 0, camYOffset = 0;
	private static JFrame frame;
	private static Screen instance = new Screen(); 
	private static BufferedImage buffer;
	private static Graphics g;

	private Screen()
	{
		// init stuff
		frame = new JFrame("Dungeon");
		frame.add(this);
		frame.setSize(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		buffer = new BufferedImage(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT, BufferedImage.TYPE_INT_ARGB);
		g = buffer.getGraphics();
		frame.setFocusable(true);
		setFocusable(true);
		requestFocusInWindow();
	}

	static void update()
	{
		instance.getGraphics().drawImage(buffer, 0, 0, Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT, null); // renders buffer on screen
		g.dispose(); // disposes g
		g = buffer.getGraphics(); // setups g (used in Screen.draw(...))
		g.setColor(Color.BLACK); // clears ...
		g.fillRect(0, 0, Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT); // ... screen
	}

	public static Graphics g() { return g; }
	public static Screen get() { return instance; }
}
