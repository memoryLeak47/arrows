package tilemap;

import entity.entities.tile.Tile;

public class GameTileMap
{
	private Tile[][] tiles;

	public GameTileMap(LobbyTileMap lobbyTileMap)
	{
		tiles = new Tile[lobbyTileMap.getInts().length][lobbyTileMap.getInts()[0].length];

		for (int x = 0; x < lobbyTileMap.getInts().length; x++)
		{
			for (int y = 0; y < lobbyTileMap.getInts()[0].length; y++)
			{
				tiles[x][y] = Tile.getByColorID(lobbyTileMap.getInts()[x][y]);
			}
		}
	}
}
