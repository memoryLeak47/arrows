package core;

import javax.swing.JFrame;
import java.awt.Dimension;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.awt.image.BufferStrategy;
import java.awt.Color;
import java.awt.Point;

import core.Main;
import misc.Debug;
import misc.JFrameListener;
import misc.math.pixel.*;

public class Screen extends Canvas
{
	public static final int WIDTH = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth(); // bildschirmbreite
	public static final int HEIGHT = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight(); // bildschirmhöhe

	private static JFrame frame; // fenster
	private static Screen instance; // singleton-instanz
	private static Graphics g; // graphics auf die BufferStrategy bs
	private static BufferStrategy bs; // backbuffer

	// ausgeführt von Main.init()
	public static void init()
	{
		instance = new Screen("Arrows"); // erstellung der singleton-instanz
	}

	private Screen(String caption)
	{
		frame = new JFrame(caption); // erstellung des fensters
		setFullscreen();
		frame.add(this); // diese Screen instanz zum fenster hinzufügen
		frame.setSize(WIDTH, HEIGHT); // größe des fensters auf die größe des bildschirms setzen
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // -> fenster schließt, wenn man auf das kreuz drückt
		frame.setVisible(true); // -> fenster ist sichtbar
		frame.setResizable(true); // -> fenstergröße ist variabel (fullscreen ist möglich)
		frame.setFocusable(true); // -> man kann das fenster focusen, listeners können nur funktionieren wenn das fenster gefocust ist
		frame.addWindowListener(new JFrameListener()); // ein neuer JFrameListener wird dem fenster hinzugefügt -> wenn es schließt wird Main.quit() ausgeführt
		requestFocusInWindow();  // das fenster wird fokusiert
	}

	private void setFullscreen()
	{
		GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
		if (!gd.isFullScreenSupported())
		{
			Debug.note("Fullscreen not supported");
			return;
		}

		// frame.setUndecorated(true); // --> TODO needed for extended-mode fullscreen (doesnt work in linux)
		try
		{
			gd.setFullScreenWindow(frame);
		}
		catch (Exception e)
		{
			Debug.error("Screen.<init>(): gd.setFullScreenWindow(frame)");
		}
	}

	// called by Main.render() in a fixed rate
	public static void render()
	{
		bs = get().getBufferStrategy(); // setzt bs auf die BufferStrategy der singleton-instanz
		if (bs == null) // falls es noch keine BufferStrategy gibt
		{
			get().createBufferStrategy(3); // erstelle sie
			return; // und beende die render funktion
		} // falls wir nun eine bufferstrategy haben
		g = bs.getDrawGraphics(); // setze g auf deren graphics
		g.setColor(Color.BLACK); // setze farbe auf schwarz
		g.fillRect(0, 0, WIDTH, HEIGHT); // fülle den bildschirm schwarz
		Main.getMenuList().render(); // render die menuList
		g.dispose(); // dispose die graphics
		bs.show(); // flip den buffer
	}

	// returt die cursor position oder null falls Maus außerhalb des fensters ist
	public static PixelPosition getCursorPosition()
	{
		Point position = get().getMousePosition();
		if (position == null) // wenn die maus außerhalb des fensters ist
		{
			Debug.warn("Screen.getCursorPosition(): mouse out of screen or simply null", Debug.Tags.EXTENDED_WARNINGS);
			return new PixelPosition(-1, -1); // return default position
		} // falls sie im fenster ist
		return new PixelPosition(position.x, position.y); // returne die maus-position
	}

	public static Graphics g() { return g; } // returnt die graphics, gebraucht zum rendern
	public static Screen get() { return instance; } // returnt die singleton-instance
	public static PixelSize getScreenSize() { return new PixelSize(WIDTH, HEIGHT); } // returnt die fenstergröße (= bildschirmgröße)
}
