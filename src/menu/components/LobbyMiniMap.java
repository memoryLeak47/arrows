package menu.components;

import menu.components.MiniMap;
import menu.ComponentContainer;
import game.tilemap.LobbyTileMap;
import misc.math.Rect;

public class LobbyMiniMap extends MiniMap
{
	public LobbyMiniMap(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	public void applyMap(int[][] map)
	{
		super.applyMap(map);
	}
}
