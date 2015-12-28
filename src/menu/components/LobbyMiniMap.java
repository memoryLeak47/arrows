package menu.components;

import menu.components.MiniMap;
import menu.ComponentContainer;
import tilemap.LobbyTileMap;
import misc.math.pixel.PixelRect;

public class LobbyMiniMap extends MiniMap
{
	public LobbyMiniMap(ComponentContainer parent, PixelRect rect)
	{
		super(parent, rect);
	}

	public void applyMap(int[][] map)
	{
		super.applyMap(map);
	}
}
