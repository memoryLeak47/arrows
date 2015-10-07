package menu.components;

import java.awt.Color;
import java.awt.image.BufferedImage;

import core.Screen;
import graphics.ImageFile;
import menu.MenuComponent;
import menu.ComponentContainer;
import misc.Debug;
import misc.math.Rect;

public class MiniMap extends MenuComponent
{
	private BufferedImage tileMapImage;

	public MiniMap(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	@Override public void render()
	{
		if (getTileMapImage() == null)
		{
			Debug.warn("MiniMap.render(): getTileMapImage() == null");
		}
		Screen.g().drawImage(getTileMapImage(), getOffset().getX(), getOffset().getY(), getWidth(), getHeight(), null);
	}

	// Getter
	protected BufferedImage getTileMapImage()
	{
		// Falls kein Image vorhanden, VOID_ICON returnen
		if (tileMapImage == null)
		{
			// Debug.warn("MiniMap.getTileMapImage(): tileMapImage == null; returns VOID_ICON");
			return ImageFile.getImageByImageID(ImageFile.VOID_ICON.getImageID());
		}
		return tileMapImage;
	}

	protected void applyMap(int[][] map)
	{
		tileMapImage = new BufferedImage(getZoom()*map.length, getZoom()*map[0].length, BufferedImage.TYPE_INT_ARGB);

		for (int x = 0; x < map.length; x++)
			for (int y = 0; y < map[0].length; y++)
			{
				for (int xZoom = 0; xZoom < getZoom(); xZoom++)
					for (int yZoom = 0; yZoom < getZoom(); yZoom++)
					{
						tileMapImage.setRGB(x+xZoom, y+yZoom, map[x][y]);
					}
			}
	}

	protected int getZoom() { return 1; }
}
