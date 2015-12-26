package menu.components;

import menu.components.MiniMap;
import menu.ComponentContainer;
import tilemap.LobbyTileMap;
import misc.math.menu.MenuRect;

public class LobbyMiniMap extends MiniMap
{
	public LobbyMiniMap(ComponentContainer parent, MenuRect rect)
	{
		super(parent, rect);
	}

	public void applyMap(int[][] map)
	{
		super.applyMap(map);
	}
}
