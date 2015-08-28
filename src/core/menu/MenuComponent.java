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
	private BufferedImage image; // image of the MenuComponent, created in updateImage(), rendered in render()

	public MenuComponent(Menu menu, Rect rect)
	{
		super(rect); // setup rect per copy-constructor
		this.menu = menu; // set owner menu
		image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB); // setup image (size=this.size)
		graphics = image.getGraphics(); // setup graphics

		// TODO: every subclass has to call updateImage() in constructor this should be taken care of by this class
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

	public final void render() // draws image to Screen
	{
		Screen.g().drawImage(image, getX(), getY(), getWidth(), getHeight(), null);
	}

	// onEventFunctions: may be overwritten by subclasses
	public void onClick(int mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}

	public abstract void updateImage(); // draws on getGraphics() -> sets image correctly

	protected void setImage(BufferedImage image) { this.image = image; }
	protected Graphics getGraphics() { return graphics; }
	public BufferedImage getImage() { return image; }
}
