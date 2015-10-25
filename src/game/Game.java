package game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import game.tilemap.LobbyTileMap;
import game.tilemap.GameTileMap;
import game.Entity;
import game.player.MinimizedGamePlayer;
import misc.Debug;

public class Game
{
	private GameTileMap tileMap;

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
	}

	// TODO
	// Returnt alle Entities außer Tiles (Player, Bullets, Cosmetics)
	public LinkedList<Entity> getDynamicEntities()
	{
		Debug.warn("Game.getDynamicEntities(): return null TODO");
		return null;
	}

	// Returnt alle Player. Gebraucht für die MiniMap
	public LinkedList<MinimizedGamePlayer> getPlayers()
	{
		Debug.warn("Game.getPlayers(): return null TODO");
		return null;
	}

	// MiniMap Hintergrund
	public BufferedImage getPixelMapImage()
	{
		Debug.warn("Game.getPixelMapImage(): return null TODO");
		return null;
	}

	// returnt die GameTileMap als ein Bild, wie es im Spiel erscheint
	public BufferedImage getMapImage()
	{
		Debug.warn("Game.getMapImage(): return null TODO");
		return null;
	}
}
