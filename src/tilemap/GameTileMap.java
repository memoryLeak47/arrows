package tilemap;

import java.util.TreeMap;

import entity.entities.tile.Tile;
import entity.entities.tile.tiles.SpawnTeamTile;
import misc.Debug;
import misc.game.Team;
import misc.math.game.GamePosition;

public class GameTileMap
{
	private Tile[][] tiles;
	private TreeMap<Team, GamePosition> spawnPositions = new TreeMap<Team, GamePosition>();
	
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

		for (int x = 0; x < tiles.length; x++)
		{
			for (int y = 0; y < tiles[0].length; y++)
			{
				if (tiles[x][y] instanceof SpawnTeamTile)
					spawnPositions.put(((SpawnTeamTile) tiles[x][y]).getTeam(), new GamePosition(x, y));
			}
		}
	}

	public GamePosition getSpawnTilePositionByTeam(Team team)
	{
		for (int x = 0; x < tiles.length; x++)
		{
			for (int y = 0; y < tiles[0].length; y++)
			{
				if (tiles[x][y] instanceof SpawnTeamTile && ((SpawnTeamTile) tiles[x][y]).getTeam() == team)
					return new GamePosition(x, y);
			}
		}
		Debug.warn("GameTileMap.getSpawnTilePositionByTeam(): no SpawnTile found for team " + team);
		return null;
	}	
}
