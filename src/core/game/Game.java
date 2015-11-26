package core.game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import tilemap.LobbyTileMap;
import tilemap.GameTileMap;
import entity.Entity;
import entity.bullet.MinimizedBullet;
import entity.cosmetic.Cosmetic;
import entity.player.MinimizedGamePlayer;
import misc.Debug;
import misc.game.kill.Kill;

public abstract class Game
{
	private GameTileMap tileMap;
	private LinkedList<Cosmetic> cosmetics;
	private LinkedList<Kill> kills;

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
	}

	abstract LinkedList<? extends MinimizedBullet> getBullets();

	// Returnt alle Entities außer Tiles (Player, Bullets, Cosmetics)
	public LinkedList<Entity> getDynamicEntities()
	{
		Debug.warn("Game.getDynamicEntities(): return null TODO");
		return null;
	}

	// Returnt alle Player. Gebraucht für die MiniMap
	public abstract LinkedList<? extends MinimizedGamePlayer> getPlayers();


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
