/*
 * speichert die map währed des LobbyMenues
 */

package game.tilemap;

import java.io.File;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

import misc.Debug;

public class LobbyTileMap
{
	private int[][] map;

	public LobbyTileMap(int[][] map)
	{
		this.map = map;
	}

	// returnt eine neue LobbyTileMap aus dem übergebenen Pfad
	public LobbyTileMap getByFile(File path)
	{
		if (!path.exists())
		{
			Debug.warn("LobbyTileMap.getByFile(): Try to Load Map \"" + path.getPath() + "\" but it does not exists");
			return null;
		}

		if (!path.isFile())
		{
			Debug.warn("LobbyTileMap.getByFile(): Try to load Map \"" + path.getPath() + "\" but it is not a File");
			return null;
		}

		BufferedImage image = null;
		try
		{
			image = ImageIO.read(path);
		} catch (Exception e)
		{
			Debug.warn("LobbyTileMap.getByFile(): can't open File \"" + path.getPath() + "\". Maybe wrong format.");
			return null;
		}

		if (image == null)
			Debug.warn("LobbyTileMap.getByFile(): returns null");

		return getByBufferedImage(image);
	}

	// returnt eine neue LobbyTileMap aus dem übergebenen image
	public static LobbyTileMap getByBufferedImage(BufferedImage image)
	{
		int[][] map = new int[image.getWidth()][image.getHeight()];

		for (int x = 0; x < image.getWidth(); x++)
		{
			for (int y = 0; y < image.getWidth(); y++)
			{
				map[x][y] = image.getRGB(x, y);
			}
		}

		return new LobbyTileMap(map);
	}
}
