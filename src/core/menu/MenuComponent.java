package core.menu;

import java.awt.image.BufferedImage;
import java.awt.Graphics;
import java.awt.Color;
import javax.imageio.ImageIO;

import misc.math.Rect;
import misc.math.Position;
import core.menu.Menu;
import core.Screen;

public abstract class MenuComponent extends Rect
{
	private Menu menu; // Menu which contains this MenuComponent
	private Graphics graphics; // Graphics of image
	private BufferedImage image; // image of the MenuComponent

	public MenuComponent(Menu menu, Rect rect)
	{
		super(rect);
		this.menu = menu; // set owner menu
		image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB); // setup image size=this.size
		graphics = image.getGraphics(); // setup graphics
	}

	protected final boolean isHovered()
	{
		return this == menu.getHoveredComponent();
	}

	protected final boolean isFocused()
	{
		return this == menu.getFocusedComponent();
	}

	public void tick() {} // TODO why this?

	public final void render()
	{
		Screen.g().drawImage(image, getX(), getY(), getWidth(), getHeight(), null); // draws image to the screen
	}

	// onEventFunctions: may be overwritten by subclasses
	public void onClick(int mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}

	public abstract void updateImage(); // sets image correctly

	protected Graphics getGraphics() { return graphics; }
	public BufferedImage getImage() { return image; }
}
