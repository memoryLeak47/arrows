package tilemap;

import java.awt.image.BufferedImage;
import java.awt.Graphics;
import java.util.TreeMap;

import static core.Main.TILESIZE;
import entity.entities.tile.Tile;
import entity.entities.tile.tiles.SpawnTeamTile;
import graphics.ImageFile;
import misc.Debug;
import misc.game.Team;
import misc.math.game.GamePosition;

public class GameTileMap
{
	private Tile[][] tiles;
	private TreeMap<Team, GamePosition> spawnPositions = new TreeMap<Team, GamePosition>();
	private BufferedImage staticImage;
	
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
		initStaticImage();
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

	// returnt Bild von der Map (nur StaticBlocks)
	// Das Bild passt sich NICHT dem Zoom an
	private void initStaticImage()
	{
		Graphics g = getStaticImage().getGraphics();
		for (int x = 0; x < tiles.length; x++)
		{
			for (int y = 0; y < tiles[0].length; y++)
			{
				g.drawImage(ImageFile.getImageByImageID(tiles[x][y].getImageID()), x * TILESIZE, y * TILESIZE, null);
			}
		}
	}

	public BufferedImage getStaticImage()
	{
		Debug.warnIf(staticImage == null, "GameTileMap.getStaticImage(): returns null");
		return staticImage;
	}
}
